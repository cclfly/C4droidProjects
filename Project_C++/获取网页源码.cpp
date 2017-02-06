extern "C"
{
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>
}
#include<unistd.h>
#include<stdint.h>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>

namespace msocket
{
	using namespace std;
	namespace socket_mode
	{
		const int client = 0;
		const int server = 1;
	};
	class msocket
	{
	  public:
	  msocket(int type, int p, int protocol = 0):mode(-1),
			was_listen(false)
		{
			socket_fd = socket(type, p, protocol);
			addr.sin_family = type;
			memset(&addr.sin_zero,0,8);
		}
		msocket(int fd, sockaddr_in& socket_addr):mode(0), was_listen(false)
		{
			socket_fd = fd;
			addr = socket_addr;
		}
		void _connect(string host, uint16_t port)
		{
			if (mode == socket_mode::server)
			{
				throw string("服务器模式，不允许连接其他服务器！");
				return;
			}
			mode = socket_mode::client;
			char buffer[33];
			hostent *host_info = gethostbyname(host.c_str());
			inet_ntop(host_info->h_addrtype, host_info->h_addr, buffer, 33);
			addr.sin_port = htons(port);
			inet_aton(buffer, &addr.sin_addr);
			if (connect(socket_fd, (sockaddr *) & addr, sizeof(sockaddr_in)) ==-1)
				throw string("错误:无法创建连接");
		}
		void _bind(string host, uint16_t port)
		{
			if (mode == socket_mode::client)
			{
				throw string("客服端模式，不允许绑定端口");
				return;
			}
			mode = socket_mode::server;
			addr.sin_port = htons(port);
			inet_aton(host.c_str(), &addr.sin_addr);
			bind(socket_fd, (sockaddr *) & addr, sizeof(sockaddr_in));
		}
		void _listen(int n)
		{
			if (mode != 1)
			{
				throw string("没有绑定端口！");
				return;
			}
			was_listen = true;
			listen(socket_fd, n);
		}
		msocket _accept()
		{
			sockaddr_in sci;
			memset(&sci.sin_zero,0,8);
			int size=sizeof(sockaddr_in);
			if (!was_listen)
			{
				throw string("没有设置监听！");
				return msocket(-2, sci);
			}
			int cs=accept(socket_fd,(sockaddr*)&sci,&size);
			return msocket(cs, sci);
		}
		void _send(const void *data, uint32_t size)
		{
			send(socket_fd, data, size, 0);
		}
		int _recv(void *data, uint32_t max_size)
		{
			return recv(socket_fd, data, max_size, 0);
		}
		void sendTo();			// UDP
		void recvFrom();
		msocket & operator<<(string str)
		{
			_send(str.c_str(), str.size() + 1);
			return *this;
		}
		template < class T > msocket & operator<<(vector < T > &data)
		{
			for (uint32_t i = 0; i < data.size(); i++)
				_send(&data[i], sizeof(T));
			return *this;
		}
		msocket & operator>>(string & str)
		{
			char ch = 0;
			int t = 1;
			for (uint32_t i = str.size() ;t; i++)
			{
				t = recv(socket_fd, &ch, 1,0);
				str.push_back(ch);
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
			return string(inet_ntoa(addr.sin_addr));
		}
		uint16_t getPort()
		{
			return ntohs(addr.sin_port);
		}
		~msocket()
		{
			shutdown(socket_fd, 2);
		}
	  private:
		bool was_listen;
		int mode;
		int type;
		int socket_fd;
		sockaddr_in addr;
#define connect _connect
#define bind _bind
#define listen _listen
#define accept _accept
#define send _send
#define recv _recv
	};

	string get(string host, uint16_t port)
	{
		stringstream ss;
		int pos=host.find('/');
		string route,hostname;
		if(pos!=-1)
		{
		route=host.substr(pos);
		hostname=host.substr(0,pos);
		}
		else
		{
		route="/";
		hostname=host;
		}
		ss<<"GET "+route+" HTTP/1.1\r\n"<<"HOST:"<<hostname<<"\r\n"<<"Accept:*/*\r\n\r\n";
		 string get_head=ss.str();
		msocket mcs(AF_INET,SOCK_STREAM);
		mcs.connect(hostname,port);
		mcs<<get_head;
		string result;
		mcs>>result;
	return result;
	}
};

#include<thread>
using namespace std;

int server()
{
	msocket::msocket mss(AF_INET,SOCK_STREAM);
	mss.bind("127.0.0.1",2333);
	mss.listen(20);
	msocket::msocket mcs=mss.accept();
	string message;
	mcs>>message;
	cout<<"Server: 来自"<<mcs.getIP()<<":"<<mcs.getPort()<<" 的消息:"<<message;
}

int client()
{
	msocket::msocket mcs(AF_INET,SOCK_STREAM);
	mcs.connect("127.0.0.1",2333);
	mcs<<string("今天没吃药，感觉自己萌萌哒！")<<string("hello,TCP!");
}

int main()
{
/*	thread t1(server);
	usleep(500000);
	thread t2(client);
	t1.join();
	t2.join();*/
	string result=msocket::get(string("www.mao-yu.net/index.php"),80);
	cout<<result<<endl<<"get end";
}