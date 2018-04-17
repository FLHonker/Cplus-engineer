/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: tcp-communication-server.cpp
*description: The server source for tcp communication program.
*
*@Version：V1.0
*@author：Frank Liu
*@time：20180416
*
*Change record 1: // Change history record, including modification date, version number, modification person and modification contents
*change-time      version          change-author         change-content

* 20180416         V1.0              Frank                  create
*******************************************************************************/
#include <iostream>
#include <winsock2.h>
#include <cstdlib>
#include <cstdio>
#pragma comment(lib, "ws2_32.lib")  //引用Ws2_32.dll动态链接库文件
#define BUFSIZE 100

using namespace std;

char recvbuf[BUFSIZE];
SOCKET sockconn;

/**
 *在一个新的线程里面接收数据
 */
DWORD WINAPI recvThread(LPVOID lpParamter)
{
	while(true)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		//接收数据
		//recv函数：接收数据，第一个参数为socket，
		//第二个参数为接收数据缓冲区，第三个参数为缓冲区的长度，第四个参数为函数的调用方式。
		recv(sockconn, recvbuf, sizeof(recvbuf), 0);
		cout << "Client:" << recvbuf << endl;
	}
	closesocket(sockconn);
}

int main()
{
	WSADATA wsaData;
	int port = 10800;   //端口号
	//WSAStartup函数：该函数用于初始化Ws2_32.dll动态链接库，
	//在使用socket之前，一定要初始化该链接库。
	//WSAStarup()第一个参数表示winsock的版本，本例使用的是winsock2.2版本。
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "Winsock初始化失败！" <<endl;
		return -1;
	}
	
	/**
	 *创建用于监听的套接字，即服务端的socket
	 */
	//SOCKET socket(int af,int type,int protocol);
	//af:一个地址家族，通常为AF_INET
	//type:套接字类型，SOCK_STREAM表示创建面向流连接的套接字。
	//为SOCK_DGRAM，表示创建面向无连接的数据包套接字。为SOCK_RAW，表示创建原始套接字。
	//protocol:套接字所用协议，不指定可以设置为0
	//返回值就是一个socket
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	//htons函数：将一个16位无符号短整型数据由主机排列方式转化为网络排列方式，htonl函数的作用恰好相反。
	addrSrv.sin_port = htons(port);
	/**
     * INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。
	 * 一般来说，在各个系统中均定义成为0值。
     */
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	/**
	 *bind函数：该函数用于将套接字绑定到指定的端口和地址。
	 *第一个参数为socket，第二个参数是一个结构指针，它包含了端口和IP地址信息，
	 *第三个参数表示缓冲区长度。需要说明的是，第二个参数在API中表示为：const struct sockaddr FAR*,
	 *这个语法结构我还没见过，网上说这是远指针，win16时期的产物，算是长见识了。
	 */
	int retVal = bind(sockServer, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if(retVal == SOCKET_ERROR)
	{
		cout << "bind失败:" << WSAGetLastError() <<endl;
		return -2;
	}else {
		cout<< "bind端口和IP...ok" <<endl;
	}
	
	/**
	 *listen函数：将socket设置为监听模式，服务端的socket特有。
	 *必须将服务端的socket设置为监听模式才能和服务端简历连接。
	 *listen()里面有两个参数，第一个参数为socket，第二个参数为等待连接最大队列的长度。
	 */
	if(listen(sockServer, 10) == SOCKET_ERROR)
	{
		cout << "监听失败:" << WSAGetLastError() <<endl;
		return -3;
	}else {
		cout<< "listen port:" << port << "...ok." <<endl;
	}
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR_IN);
	
	//等待客户端请求到来
	while(true)
	{
		/*
		 *accept函数：服务端socket接收客户端的连接请求，连接成功，则返回一个socket，
		 *该socket可以在服务端发送和接收数据。第一个参数为socket，第二个参数为包含客户端
		 *端口IP信息的sockaddr_in结构指针，第三个参数为接收参数addr的长度。
		*/
		sockconn = accept(sockServer, (SOCKADDR*)&addrClient, &len);
		if(sockconn == SOCKET_ERROR)
		{
			cout<<"等待请求连接失败！"<<WSAGetLastError() <<endl;
			break;
		} else {
			cout << "连接建立..." <<endl;
		}
		
		cout<< "客户端IP是:[" << inet_ntoa(addrClient.sin_addr) << "]" <<endl;
		
		//发送数据
		char sendbuf[BUFSIZE] = "你好，我是服务器，咱们一起聊天吧！";
		cin >> sendbuf;
		//send函数：发送数据，里面的参数基本和recv()一样。
		int iSend = send(sockconn, sendbuf, sizeof(sendbuf), 0);
		if(iSend == SOCKET_ERROR)
		{
			cout << "发送数据失败！" <<endl;
			break;
		}
		
		/*
		HANDLE WINAPI CreateThread(
    		LPSECURITY_ATTRIBUTES   lpThreadAttributes, //线程安全相关的属性，常置为NULL
    		SIZE_T                  dwStackSize,        //新线程的初始化栈在大小，可设置为0
    		LPTHREAD_START_ROUTINE  lpStartAddress,     //被线程执行的回调函数，也称为线程函数
    		LPVOID                  lpParameter,        //传入线程函数的参数，不需传递参数时为NULL
    		DWORD                   dwCreationFlags,    //控制线程创建的标志
    		LPDWORD                 lpThreadId          //传出参数，用于获得线程ID，如果为NULL则不返回线程ID
		);
		*/
		HANDLE hThread = CreateThread(NULL, 0, recvThread, NULL, 0, NULL);
		CloseHandle(hThread);
	}
	

	//closesocket函数：关闭socket，里面的唯一的一个参数就是要关闭的socket。
	closesocket(sockServer);
	WSACleanup();   //释放初始化Ws2_32.dll所分配的资源
	system("pause");
	return 0;
}
