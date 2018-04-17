/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: tcp-communication-client.cpp
*description: The client source for tcp communication program.
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
#include <cstdio>
#include <cstdlib>
#pragma comment(lib, "ws2_32.lib")  //引用库文件
#define BUFSIZE 1024

using namespace std;

int main()
{
	//加载套接字
	WSADATA wsaData;
	char buff[BUFSIZE];
	memset(buff, 0, sizeof(buff));
	
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "Winsock初始化失败！" <<endl;
		return -1;
	}
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(10800);   //server port
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if(sockClient == SOCKET_ERROR)
	{
		cout<< "socket error:" << WSAGetLastError() <<endl;
		return -2;
	}

	//向服务器发出连接请求
	cout << "正在连接Server..." <<endl;
	/*
	 *connect函数：客户端socket发送连接请求的函数，第一个参数是客户端的socket，
	 *第二个参数是一个结构体指针，里面包括连接主机的地址和ip，第三个参数为缓冲区的长度。
	*/
	if(connect(sockClient, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		cout << "connect failed: " << WSAGetLastError() <<endl;
		return -3;
	}else {
		//接收数据
		recv(sockClient, buff, sizeof(buff), 0);
		cout << "Server:" << buff <<endl;
	}
	
	//发送数据
	char sendbuf[BUFSIZE] = "下面咱们开始聊天啦！";
	//cin >> sendbuf;
	send(sockClient, sendbuf, sizeof(sendbuf), 0);
	//不断输入，然后发送
	while(true)
	{
		cin >> sendbuf;
		//cout << "Client:" << sendbuf <<endl;
		send(sockClient, sendbuf, sizeof(sendbuf), 0);
	}
	
	//关闭套接字
	closesocket(sockClient);
	WSACleanup(); //释放初始化Ws2_32.dll所分配的资源
	system("pause");
	return 0;
}
