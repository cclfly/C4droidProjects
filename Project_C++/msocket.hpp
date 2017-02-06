/*
项目:Mao-Yu's socket C++ library
Version:0.2.4
完成度:Linux完成，Windows完成
完成基本的post,get操作
下一目标:完善报错
*/
#ifndef _H_MSOCKET_
#define _H_MSOCKET_

#ifndef _WIN32
extern "C"
{
#include <sys/socket.h>
#include <arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
}
#else
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#define close closesocket
#undef s_addr
#pragma comment(lib,"ws2_32.lib")
#endif

#include <cerrno>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace msocket
{
	using namespace std;
	namespace socket_mode
	{
		const int client = 0;
		const int server = 1;
	};
	enum msocket_type
	{
		MSOCKET_TCP,
		MSOCKET_UDP
	};
	struct msocket_addr
	{
		uint16_t sin_family;
		uint16_t sin_port;
		struct in_addr{ uint32_t s_addr; }sin_addr;
		uint8_t sin_zero[8];
	};
	class msocket
	{
	public:
		msocket(msocket_type type) :mode(-1), was_listen(false)
		{
#ifdef _WIN32
			if (object_num++ == 0)
				WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
			int _type;
			switch (type)
			{
			case MSOCKET_TCP:
				_type = SOCK_STREAM;
				break;
			case MSOCKET_UDP:_type = SOCK_DGRAM;
				break;
			}
			socket_fd = socket(AF_INET, _type, 0);
			this->type = _type;
			addr.sin_family = AF_INET;
			target_addr.sin_family = AF_INET;
			memset(&addr.sin_zero, 0, 8);
			memset(&target_addr.sin_zero, 0, 8);
		}

		msocket(int domain, int _type, int protocol = 0) :mode(-1), was_listen(false), type(_type)
		{
#ifdef _WIN32
			if (object_num++ == 0)
				WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
			socket_fd = socket(domain, type, protocol);
			addr.sin_family = domain;
			target_addr.sin_family = domain;
			memset(&addr.sin_zero, 0, 8);
			memset(&target_addr.sin_zero, 0, 8);
		}

		msocket(int fd, msocket_addr & socket_addr, int _type) :mode(0), was_listen(false), type(_type)
		{
#ifdef _WIN32
			if (object_num++ == 0)
				WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
			socket_fd = fd;
			addr = socket_addr;
		}

		void setSocketOpt(int optname, int value)
		{
#ifdef _WIN32
			setsockopt(socket_fd, SOL_SOCKET, optname, (char*)&value, sizeof(int));
#else
			setsockopt(socket_fd, SOL_SOCKET, optname, &value, sizeof(int));
#endif
		}

		void _connect(string host, uint16_t port)
		{
			if (mode == socket_mode::server)
			{
				throw string("服务器模式，不允许连接其他服务器！");
				return;
			}
			hostent *host_info = gethostbyname(host.c_str());
			if (host_info == nullptr)
				throw string("connect:无效的主机名或IP!");
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = *(uint32_t*)host_info->h_addr;
			if (connect(socket_fd, (sockaddr *)& addr, sizeof(msocket_addr)) == -1)
				throw string("connect:错误:无法创建连接 ") + getError();
			mode = socket_mode::client;
		}

		void _bind(string host, uint16_t port)
		{
			if (mode == socket_mode::client)
			{
				throw string("客服端模式，不允许绑定端口");
				return;
			}
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(host.c_str());
			if (bind(socket_fd, (sockaddr *)& addr, sizeof(msocket_addr)) == -1)
			{
				throw string("bind:绑定端口失败 ") + getError();
				return;
			}
			mode = socket_mode::server;
		}

		void _listen(int n)
		{
			if (type == SOCK_STREAM)
			{
				if (mode != socket_mode::server)
				{
					throw string("listen:没有绑定端口！");
					return;
				}
				was_listen = true;
				listen(socket_fd, n);
			}
		}

		msocket _accept()
		{
			msocket_addr sci;
			memset(&sci.sin_zero, 0, 8);
			int size = sizeof(msocket_addr);
			if (!was_listen)
			{
				throw string("accept:没有设置监听！");
				return msocket(-2, sci, type);
			}
			int cs = accept(socket_fd, (sockaddr *)& sci, &size);
			return msocket(cs, sci, type);
		}

		int _send(const char *data, uint32_t size)
		{
			if (type == SOCK_STREAM)
				return send(socket_fd, data, size, 0);
			return -1;
		}

		int _recv(char *data, uint32_t max_size)
		{
			if (type == SOCK_STREAM)
				return recv(socket_fd, data, max_size, 0);
			return -2;
		}

		int setTargetAddr(string host, uint16_t port)
		{
			if (type == SOCK_DGRAM)
			{
				target_addr.sin_port = htons(port);
				hostent *host_info = gethostbyname(host.c_str());
				if (host_info == nullptr)
					throw string("setTargetAddr:无效的主机名或IP!");
				addr.sin_addr.s_addr = *(uint32_t*)host_info->h_addr;
			}
		}

		int sendTo(const char *data, uint32_t size)
		{
			if (type == SOCK_DGRAM)
				return sendto(socket_fd, data, size, 0, (sockaddr *)& target_addr, sizeof(msocket_addr));
			return -2;
		}

		int recvFrom(char *data, uint32_t max_size)
		{
			if (type == SOCK_DGRAM)
			{
				int size = sizeof(msocket_addr);
				return recvfrom(socket_fd, data, max_size, 0, (sockaddr *)& target_addr, &size);
			}
			return -2;
		}

		msocket & operator<<(string str)
		{
			int t=0;
			if (type == SOCK_STREAM)
				_send(str.c_str(), str.size());
			if (type == SOCK_DGRAM)
				sendTo(str.c_str(), str.size());
			if (t == -1)
				throw string("无法获取数据");
			return *this;
		}

		template < typename T > msocket & operator<<(vector < T > &data)
		{
			int t = 0;
			if (!data.empty())
			{
				if (type == SOCK_STREAM)
					_send(&data[0], sizeof(T)*data.size());
				if (type == SOCK_DGRAM)
					sendTo(&data[0], sizeof(T)*data.size());
				if (t == -1)
					throw string("无法获取数据");
			}
			return *this;
		}

		template < typename T > msocket & operator>>(vector < T > &data)
		{
			int t = sizeof(T) * 128;
			T buffer[128];
			while (t == sizeof(T) * 128)
			{
				if (type == SOCK_STREAM)
					t = _recv(buffer, sizeof(T) * 128);
				if (type == SOCK_DGRAM)
					t = recvFrom(buffer, sizeof(T) * 128);
				for (int i = 0; i < (t / sizeof(T)); i++)
					data.push_back(buffer[i]);
				if (t == -1)
				{
					throw string("无法获取数据");
					return *this;
				}
			}
			return *this;
		}

		msocket & operator>>(string & str)
		{
			int t = 2048;
			char buffer[2048];
			while (t == 2048)
			{
				if (type == SOCK_STREAM)
					t = _recv(buffer, 2048);
				if (type == SOCK_DGRAM)
					t = recvFrom(buffer, 2048);
				for (int i = 0; i < t; i++)
					str.push_back(buffer[i]);
				if (t == -1)
				{
					throw string("无法获取数据");
					return *this;
				}
			}
			return *this;
		}

		bool state()
		{
			if (socket_fd > -2)
				return 1;
			return 0;
		}

		string getIP()
		{
			return string(inet_ntoa(*(in_addr*)&addr.sin_addr));
		}

		uint16_t getPort()
		{
			return ntohs(addr.sin_port);
		}

		string getTargetIP()
		{
			if (type == SOCK_DGRAM)
				return string(inet_ntoa(*(in_addr*)&target_addr.sin_addr));
			return string("0.0.0.0");
		}

		uint16_t getTargetPort()
		{
			if (type == SOCK_DGRAM)
				return ntohs(target_addr.sin_port);
			return 0;
		}

		char* getError()
		{
			return strerror(errno);
		}

		~msocket()
		{
			close(socket_fd);
#ifdef _WIN32
			if (--object_num == 0)
				WSACleanup();
#endif
		}
	private:
		bool was_listen;
		int mode;
		int socket_fd;
		int type;
		msocket_addr addr;
		msocket_addr target_addr;
#ifdef _WIN32
		static uint32_t object_num;
		static WSADATA wsaData;
#endif

#define connect _connect
#define bind _bind
#define listen _listen
#define accept _accept
#define send _send
#define recv _recv
	};
#ifdef _WIN32
	uint32_t msocket::object_num = 0;
	WSADATA msocket::wsaData;
#endif
	string get(string host, bool show_head = false, uint16_t port = 80)
	{
		// 临时方案
		stringstream ss;
		int pos = host.find('/');
		string route, hostname;
		if (pos != -1)
		{
			route = host.substr(pos);
			hostname = host.substr(0, pos);
		}
		else
		{
			route = "/";
			hostname = host;
		}
		ss << "GET " << route << " HTTP/1.1\r\n" << "HOST:" << hostname << "\r\n" << "Accept:*/*\r\n" << "\r\n";
		string get_head = ss.str();
		ss.str("");
		ss.clear();
		msocket mcs(MSOCKET_TCP);
		try
		{
			mcs.connect(hostname, port);
		}
		catch (string e)
		{
			throw e;
			return "";
		}
		mcs << get_head;
		string result;
		mcs >> result;
		if (!result.empty())
		{
			ss.str(result);
			string temp;
			while (!ss.eof())
			{
				getline(ss, temp);
				if (temp.find("Content-Length:") != -1)
					break;
			}
			if (!show_head)
				result = result.substr(result.find("\r\n\r\n") + 4);
			if (!temp.empty())
			{
				string length_str = temp.substr(15);
				for (auto i = length_str.begin(); i != length_str.end(); i++)
					if (*i == ' ')
						i = length_str.erase(i);
				int length;
				ss.str(length_str);
				ss >> length;
				int current_length = result.size();
				char buffer[2048];
				while (current_length < length)
				{
					int t = mcs.recv(buffer, 2048);
					for (int i = 0; i < t; i++)
						result.push_back(buffer[i]);
					current_length += t;
				}
			}
		}
		return result;
	}

	string post(string host, bool show_head = false, uint16_t port = 80, string data = "")
	{
		// 临时方案
		stringstream ss;
		int pos = host.find('/');
		string route, hostname;
		if (pos != -1)
		{
			route = host.substr(pos);
			hostname = host.substr(0, pos);
		}
		else
		{
			route = "/";
			hostname = host;
		}
		ss << "POST " << route << " HTTP/1.1\r\n" << "HOST:" << hostname << "\r\n" << "Accept:*/*\r\n" << "Content-Length:" << (data.empty() ? 0 : data.size()) << "\r\n" << "Content-Type:application/x-www-form-urlencoded" << "\r\n" << "\r\n" << data;
		string post_head = ss.str();
		ss.str("");
		msocket mcs(MSOCKET_TCP);
		try
		{
			mcs.connect(hostname, port);
		}
		catch (string e)
		{
			throw e;
			return "";
		}
		mcs << post_head;
		string result;
		mcs >> result;
		if (!result.empty())
		{
			ss.str(result);
			string temp;
			while (!ss.eof())
			{
				getline(ss, temp);
				if (temp.find("Content-Length:") != -1)
					break;
			}
			if (!show_head)
				result = result.substr(result.find("\r\n\r\n") + 4);
			if (!temp.empty())
			{
				string length_str = temp.substr(15);
				for (string::iterator i = length_str.begin(); i != length_str.end(); i++)
					if (*i == ' ')
						i = length_str.erase(i);
				int length;
				ss.str(length_str);
				ss >> length;
				int current_length = result.size();
				char buffer[2048];
				while (current_length < length)
				{
					int t = mcs.recv(buffer, 2048);
					for (int i = 0; i < t; i++)
						result.push_back(buffer[i]);
					current_length += t;
				}
			}
		}
		return result;
	}
};
#endif