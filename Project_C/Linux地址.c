// all.h
// 2005/06/20,a.m. wenxy
#ifndef _ALL_H
#define _ALL_H
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <errno.h> 
// ---------------------
// ＞＞?：ARP＜┨μ?┴，???t
#include<netinet/in.h>
#include<arpa/inet.h>
/* #include<linux/if_ether.h> */ 
#include<ctype.h>
#include <fcntl.h>
// ---------------------
#include <unistd.h>
#include <string>
#include <iostream>
using namespace std;
#define MAX_MAC_LEN 24 // MAC〜?＞??o3???μ?〜?＞┏3∴?┬(byte)
#define COMPART_MAC ":" // MAC〜?＞?μ?，???，?, Warnning:DT??＞?o┷♀?＼?D??┫DT???＞3━D┛!!!
#endif /* end _ALL_h */
// end file
// main.cpp
// 2005/06/20,a.m. wenxy
#include "all.h"
// function declare
static string GetLocalMac(string & strEth); // get loacl NIC's MAC
void set_ip_addr(char *,char *); // ━?3?IP
void set_hw_addr(char buf[], char *str); // ━?3?MAC
static string GetMacByIP(string strSrcIP, string strSrcMAC, string strDesIP ,string strNIC); // ??┬????：IPμ?MAC
/*
#define SRC_IP "10.0.1.77" // ?＞IP
#define DES_IP "10.0.1.35" // ??μ?IP
#define LOCAL_HW "00:C0:4C:39:0D:6F" // 10.0.1.77μ?eth0μ?MAC
#define DEVICE "eth0" // ?┏?┣
*/
#define PADD_MAC "00:00:00:00:00:00" // ━?3?μ?MAC
#define DES_MAC "FF:FF:FF:FF:FF:FF" // 1?2�MAC
#define ARP_SEND_COUNT 3 // ，♂?┴ARP???┏μ?ARP＜┨μ???┷y 
struct ether_header
{
unsigned char ether_dhost[6]; /* destination eth addr */
unsigned char ether_shost[6]; /* source ether addr */
unsigned short ether_type; /* packet type ID field */
};
struct arp_header
　　{
　　 unsigned short int ar_hrd; /* Format of hardware address. */
　　 unsigned short int ar_pro; /* Format of protocol address. */
　　 unsigned char ar_hln; /* Length of hardware address. */
　　 unsigned char ar_pln; /* Length of protocol address. */
　　 // -------------------------
　　 unsigned short int ar_op; /* ARP opcode (command). */
　　 unsigned char __ar_sha[6]; /* Sender hardware address. */
　　 unsigned char __ar_sip[4]; /* Sender IP address. */
　　 unsigned char __ar_tha[6]; /* Target hardware address. */
　　 unsigned char __ar_tip[4]; /* Target IP address. */
　　 // -------------------------
　　};
　　struct arp_packet
　　{
　　 struct ether_header ethhdr;
　　 struct arp_header arphdr;
　　 unsigned char padding[18]; /* filled with 0 */
　　};
　　/* arp reply:
　　* op = 2
　　* ethhdr.ether_dhost = arphdr.__ar_tha = switch hard addr
　　* ethhdr.ether_shost = arphdr.__ar_sha = local hard addr
　　* arphdr.__ar_tip = switch ip
　　* arphdr.__ar_sip = victim ip
　　*/
　　#define FRAME_TYPE 0x0806 /* arp=0x0806,rarp=0x8035 */
　　#define HARD_TYPE 1 /* ethernet is 1 */
　　#define PROTO_TYPE 0x0800 /* IP is 0x0800 */
　　#define OP_CODE 1 /* arp=1/2,1?a???┏♀?2?a┏|＞e,rarp=3/4 */
　　 
　　// linux????┬?LAN┐????：IPμ?┴??：MAC
　　// In: argv[1]:＼??┣IP♀?argv[2]:??μ?IP
　　// Out: 
　　int main( int argc, char *argv[] )
　　{
　　string strETH; // ＼??┣NIC??3?
　　string strLocalMAC; // ＼??┣MAC
　　string strSrcIP; // ＼??┣IP
　　string strDesMAC; // ??μ?MAC
　　string strDesIP; // ??μ?IP
　　// ?━2└2?┷y
　　if ( argc != 4 )
　　{
　　 printf("Useage: get_mac [interface name of the IP] [IP] [ARP IP]\n\n");
　　 return 0;
　　} 
　　strETH = argv[1]; //"eth0";
　　strSrcIP = argv[2]; //"10.0.1.77";
　　strDesIP = argv[3]; //"10.0.1.69";
　　printf("Run ......\n");
　　printf("??┬? %s ?┏?┣μ?MAC ......\n", strETH.c_str());
　　// ??┬????：NIC??3?μ?MAC
　　strLocalMAC = GetLocalMac(strETH); 
　　#if 0
　　printf("Note: %s[%s]\n", strETH.c_str(), strLocalMAC.c_str());
　　#endif
　　// ??┬????：?┏?┣MAC
　　if ( 0 == strcmp( (const char*)strLocalMAC.c_str(), (const char*)"") )
　　{
　　 printf("Error: call strcmp() failed\n");
　　 printf("--------------------------------\n\n");
　　 return -1;
　　}
　　else
　　{
　　 printf("??┬??┏?┣MAC3└1|: %s [%s]\n", strETH.c_str(), strLocalMAC.c_str()); 
　　}
　　// ??┬????：IP┴??：μ?MAC
　　strDesMAC = GetMacByIP(strSrcIP, strLocalMAC, strDesIP, strETH); 
　　printf("strDesMAC = %s\n", strDesMAC.c_str());
　　// 
　　return 0;
　　}
　　// ??┬?＼?μ??3┴??：μ?MAC
　　// In: strEth
　　// Out: ┬?3└1|♀?，μ??MAC〜?，?＞?♀?┷′＜┨♀?，μ??""(??＞?)
　　static string GetLocalMac(string & strEth)
　　{
　　string strLocalMAC;
　　int s;
　　struct ifreq buffer;
　　char chBuff[MAX_MAC_LEN];
　　memset(chBuff, 0x0, sizeof(chBuff));
　　//arp_process(NULL); 
　　s = socket(PF_INET, SOCK_DGRAM, 0); 
　　if (-1 == s)
　　{
　　 printf("Error: create socket failture\n");
　　 printf("--------------------------------\n\n");
　　 return "";
　　} 
　　memset(&buffer, 0x00, sizeof(buffer)); 
　　strcpy(buffer.ifr_name, strEth.c_str()); // "eth0" 
　　if ( -1 == ioctl(s, SIOCGIFHWADDR, &buffer))
　　{
　　 printf("Error: ??┬??┏?┣ %S MAC ┷′＜┨\n", strEth.c_str());
　　 printf("--------------------------------\n\n");
　　 return ""; 
　　} 
　　close(s);
　　 
　　for( s = 0; s < 6; s++ )
　　{
　　 memset(chBuff, 0x0, sizeof(chBuff));
　　 sprintf( chBuff, "%.2X", (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
　　 strLocalMAC += chBuff;
　　 
　　 //printf("%.2X", (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
　　 if (s < 5)
　　 {
　　 memset(chBuff, 0x0, sizeof(chBuff));
　　 sprintf( chBuff, "%s", COMPART_MAC);
　　 strLocalMAC += chBuff;
　　 //printf(":");
　　 }
　　} 
　　//printf("\n");
　　 
　　return strLocalMAC; 
　　}
　　//-------------------------------------------------------
　　// ，♂?┴ARP＜┨♀?2♂?┏┷?ARP┏|＞e＜┨♀?┬?3?MAC
　　// In: strSrcIP:＼??┣IP♀?strSrcMAC:＼??┣IPμ?MAC♀?strDesIP:＼????┏┏|＞eMACμ?IP , strNIC:＼?μ??┏?┣??
　　// Out: ┬?3└1|♀?，μ??MAC♀?┷′＜┨，μ??""(??＞?)
　　static string GetMacByIP(string strSrcIP, string strSrcMAC, string strDesIP ,string strNIC)
　　{
　　int sockfd; // socket handle
　　struct arp_packet arp; // arp ???┏＜┨
　　struct arp_packet arpRes; // arp ┏|┏?＞e＜┨
　　struct sockaddr sa; // eth
　　char chSrcIP[24];
　　char chDesIP[24];
　　char chSrcMAC[24];
　　char chNIC[8]; 
　　memset(chSrcIP, 0x00, sizeof(chSrcIP));
　　memset(chDesIP, 0x00, sizeof(chDesIP));
　　memset(chSrcMAC, 0x00, sizeof(chSrcMAC));
　　memset(chNIC, 0x00, sizeof(chNIC));
　　sprintf(chSrcIP, "%s", strSrcIP.c_str());
　　sprintf(chDesIP, "%s", strDesIP.c_str());
　　sprintf(chSrcMAC, "%s", strSrcMAC.c_str());
　　sprintf(chNIC, "%s", strNIC.c_str()); 
　　#define SRC_IP chSrcIP // ?＞IP
　　#define DES_IP chDesIP // ??μ?IP
　　#define LOCAL_HW chSrcMAC // eth0μ?MAC 
　　#define DEVICE chNIC // ＼??┣?┏?┣??
　　 
　　memset(&arp, 0x00, sizeof(arp));
　　memset(&arpRes, 0x00, sizeof(arpRes));
　　#if 1
　　printf("?＞IP[%s] ?＞MAC[%s] ??μ?IP[%s]\n", strSrcIP.c_str(), strSrcMAC.c_str(), strDesIP.c_str()); 
　　#endif
　　sockfd = socket(AF_INET, SOCK_PACKET, htons(0x0806));
　　if(sockfd < 0)
　　{
　　 printf("Error: create socket failed\n");
　　 printf("--------------------------------\n\n"); 
　　 return "";
　　}
　　/*
　　// └┬??socket?a，?〜┬┬??♀┷?
　　if ( -1 != fcntl(sockfd, F_SETFL, O_NONBLOCK) )
　　{
　　 printf("└┬??socket?a，?〜┬┬??♀┷?3└1|\n");
　　}
　　else
　　{
　　 printf("Warning: └┬??socket?a，?〜┬┬??♀┷?┷′＜┨[errno = %d]\n", errno);
　　}
　　*/
　　// └┬??socket?┏┷?3?┷＼
　　struct timeval tv;
　　tv.tv_sec = 0;
　　tv.tv_usec= 100;
　　if ( 0 == setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) )
　　{
　　 printf("└┬??socket?┏┷?3?┷＼3└1|\n"); 
　　}
　　else
　　{
　　 printf("Warning: └┬??socket?┏┷?3?┷＼┷′＜┨[errno = %d]\n", errno);
　　}
　　#if 1
　　printf("＞＞?：socket SOCK_PACKET 3└1|\n");
　　printf("Note: ＞＞?：ARP???┏＜┨ ......\n");
　　printf("--------------------------------\n\n"); 
　　#endif
　　// ＞＞?：ARP???┏＜┨ 
　　/* init arp packet header */
　　arp.ethhdr.ether_type = htons(FRAME_TYPE);
　　set_hw_addr( (char *)arp.ethhdr.ether_dhost, DES_MAC ); 
　　set_hw_addr( (char *)arp.ethhdr.ether_shost, LOCAL_HW );
　　#if 1
　　printf("%x|", arp.ethhdr.ether_type);
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.ethhdr.ether_dhost[i]); 
　　}
　　printf("|");
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.ethhdr.ether_shost[i]); 
　　} 
　　printf("\n--------------------------------\n"); 
　　printf("3?┷??．ARP＜┨??┴，(┛?━?┴?┷〜2?)3└1|\n\n"); 
　　#endif 
　　 
　　/* init arp packet data */ 
　　printf("3?┷??．ARP＜┨??┷y?Y(ARP???┏，?〜└) ......\n"); 
　　printf("--------------------------------\n"); 
　　arp.arphdr.ar_hrd = htons(HARD_TYPE); // 1
　　arp.arphdr.ar_pro = htons(PROTO_TYPE); // 0x0800
　　arp.arphdr.ar_op = htons(OP_CODE); // 1
　　arp.arphdr.ar_hln = (unsigned char)(6);
　　arp.arphdr.ar_pln = (unsigned char)(4);
　　#if 1
　　printf("%d|%d|%d|%d|%d|\n", arp.arphdr.ar_hrd, arp.arphdr.ar_pro, arp.arphdr.ar_op, arp.arphdr.ar_hln, arp.arphdr.ar_pln);
　　printf("--------------------------------\n"); 
　　#endif
　　set_hw_addr((char *)arp.arphdr.__ar_tha, DES_MAC); // ???┏IPμ?MAC 
　　set_hw_addr((char *)arp.arphdr.__ar_sha, LOCAL_HW); // ，♂?┴??μ?MAC 
　　set_ip_addr((char *)arp.arphdr.__ar_tip, DES_IP); // ???┏MACμ?IP 
　　set_ip_addr((char *)arp.arphdr.__ar_sip, SRC_IP); // ?＞IP
　　bzero(arp.padding, 18); // ━?3?18??〜??┣
　　#if 1 
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.arphdr.__ar_sha[i]); 
　　}
　　printf("|");
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.arphdr.__ar_sip[i]); 
　　}
　　printf("|"); 
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.arphdr.__ar_tha[i]); 
　　}
　　printf("|");
　　for (int i = 0; i < 6; i++)
　　{
　　 printf("%d_", arp.arphdr.__ar_tip[i]); 
　　}
　　printf("|");
　　printf("\n--------------------------------\n"); 
　　#endif
　　 
　　/* send arp reply packet */
　　memset(&sa, 0x00, sizeof(sa));
　　strcpy(sa.sa_data, DEVICE);
　　// ，♂?┴ARP＜┨
　　int nSendCount = ARP_SEND_COUNT;
　　while( (nSendCount --) > 0)
　　{
　　 printf("，♂?┴ARP???┏＜┨[%d Bytes]...... [μ┣%d??]\n", sizeof(arp), nSendCount); 
　　 if( sendto(sockfd, &arp, sizeof(arp), 0, (struct sockaddr*) &sa, sizeof(sa)) < 0 )
　　 {
　　 printf("Error: ，♂?┴ARP＜┨┷′＜┨ [errno = %d]\n", errno);
　　 return "";
　　 }
　　}
　　// ?┏┷?ARP┏|＞e＜┨
　　printf("NOte: ?┏┷?ARP┏|＞e ......\n");
　　int nTryCount = 5;
　　int nRecvByte = 0;
　　int nAddrLen = sizeof(sa);
　　do
　　{
　　 nRecvByte = recvfrom(sockfd, &arpRes, sizeof(arpRes),0, (struct sockaddr*)&sa, (socklen_t*)&nAddrLen); 
　　 
　　 // ┬?┷??┫???┏IPμ?ARP┏|＞e＜┨♀?┴?3?while
　　 string strTarIP; /* Target IP address */
　　 if ( nRecvByte >= 60 && 2 == ntohs(arpRes.arphdr.ar_op) )
　　 {
　　 char chBuff[MAX_MAC_LEN]; 
　　 string strTarIP; /* Target IP address */
　　 // ??┷??．IP
　　 for (int s = 0; s < 4; s++)
　　 {
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%d", (unsigned char)arpRes.arphdr.__ar_sip[s]);
　　 strTarIP += chBuff;
　　 if (s < 3)
　　 {
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%s", ".");
　　 strTarIP += chBuff;
　　 }
　　 }
　　 if ( !strcmp(strTarIP.c_str(), strDesIP.c_str()) )
　　 {
　　 printf("\n???┏IP[%s] = ┏|＞eIP[%s]\n", strDesIP.c_str(), strTarIP.c_str());
　　 break;
　　 }
　　 }
　　}while( nTryCount -- ); // ?┏┷?ARP┏|＞e＜┨μ?＞?┷y
　　printf("┛??┏┷?μ?ARP┏|＞e＜┨ [%d Bytes]\n", nRecvByte);
　　// ?┏┷?3?┷＼♀??┛＞┴?┏
　　if ( nRecvByte == -1 )
　　{
　　 printf("Warning: ?┏┷?3?┷＼♀??┛?????┣[%s]??┏D?━┏|\n", strDesIP.c_str());
　　 close(sockfd);
　　 return "";
　　}
　　printf("，???ARP┏|＞e＜┨ ......\n"); 
　　char chBuff[MAX_MAC_LEN]; 
　　string strTarIP; /* Target IP address */
　　string strTarMAC; /* Target hardware address */
　　memset(chBuff, 0x00, sizeof(chBuff));
　　// ??┷??．IP
　　for (int s = 0; s < 4; s++)
　　{
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%d", (unsigned char)arpRes.arphdr.__ar_sip[s]);
　　 strTarIP += chBuff;
　　 if (s < 3)
　　 {
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%s", ".");
　　 strTarIP += chBuff;
　　 }
　　} 
　　// ??┷??．MAC
　　memset(chBuff, 0x00, sizeof(chBuff));
　　for (int s = 0; s < 6; s++)
　　{
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%02X", (unsigned char)arpRes.arphdr.__ar_sha[s]);
　　 strTarMAC += chBuff;
　　 if (s < 5)
　　 {
　　 memset(chBuff, 0x00, sizeof(chBuff));
　　 sprintf( (char *)chBuff, "%s", COMPART_MAC);
　　 strTarMAC += chBuff;
　　 }
　　}
　　// ┷?3???μ?IP♀???μ?MAC 
　　printf("┏|＞eIP[%s] ??┏|μ?MAC[%s]\n", strTarIP.c_str(), strTarMAC.c_str());
　　printf("\n--------------------------------\n\n");
　　close(sockfd); 
　　// ，μ??＼????┏μ?MAC 
　　return strTarMAC; 
　　/* return */
　　}
　　 
　　 
　　// ━?3?MAC 
　　void set_hw_addr (char buf[], char *str)
　　{
　　 int i;
　　 char c, val;
　　 for(i = 0; i < 6; i++)
　　 {
　　 if (!(c = tolower(*str++)))
　　 perror("Invalid hardware address"),exit(1);
　　 if (isdigit(c))
　　 val = c - '0';
　　 else if (c >= 'a' && c <= 'f')
　　 val = c-'a'+10;
　　 else
　　 perror("Invalid hardware address"),exit(1);
　　 buf[i] = val << 4;
　　 if (!(c = tolower(*str++)))
　　 perror("Invalid hardware address"),exit(1);
　　 if (isdigit(c))
　　 val = c - '0';
　　 else if (c >= 'a' && c <= 'f')
　　 val = c-'a'+10;
　　 else
　　 perror("Invalid hardware address"),exit(1);
　　 buf[i] |= val;
　　 if (*str == ':')
　　 str++;
　　 }
　　}
　　// ━?3?IP
　　void set_ip_addr(char *buf, char *str)
　　{
　　 struct in_addr addr;
　　 memset(&addr, 0x00, sizeof(addr));
　　 addr.s_addr = inet_addr(str); 
　　 memcpy(buf, &addr, 4);
　　}
　　//-------------------------------------------------------
　　// end file
　　# makefile
　　bin = get_mac
　　objets = main.o
　　rubbish = $(objets) $(bin)
　　$(bin) : main.o
　　g++ -o $(bin) main.o
　　main.o : main.cpp all.h
　　g++ -c main.cpp
　　.PHONY : clean
　　clean :
　　-rm $(rubbish) 
　　# end makefile(藍劾利大 wangchao.net.cn)