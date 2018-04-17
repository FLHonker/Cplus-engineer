/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: tcp-communication-client.cpp
*description: The client source for tcp communication program.
*
*@Version��V1.0
*@author��Frank Liu
*@time��20180416
*
*Change record 1: // Change history record, including modification date, version number, modification person and modification contents
*change-time      version          change-author         change-content

* 20180416         V1.0              Frank                  create
*******************************************************************************/
#include <iostream>
#include <winsock2.h>
#include <cstdio>
#include <cstdlib>
#pragma comment(lib, "ws2_32.lib")  //���ÿ��ļ�
#define BUFSIZE 1024

using namespace std;

int main()
{
	//�����׽���
	WSADATA wsaData;
	char buff[BUFSIZE];
	memset(buff, 0, sizeof(buff));
	
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "Winsock��ʼ��ʧ�ܣ�" <<endl;
		return -1;
	}
	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(10800);   //server port
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//�����׽���
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if(sockClient == SOCKET_ERROR)
	{
		cout<< "socket error:" << WSAGetLastError() <<endl;
		return -2;
	}

	//�������������������
	cout << "��������Server..." <<endl;
	/*
	 *connect�������ͻ���socket������������ĺ�������һ�������ǿͻ��˵�socket��
	 *�ڶ���������һ���ṹ��ָ�룬����������������ĵ�ַ��ip������������Ϊ�������ĳ��ȡ�
	*/
	if(connect(sockClient, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		cout << "connect failed: " << WSAGetLastError() <<endl;
		return -3;
	}else {
		//��������
		recv(sockClient, buff, sizeof(buff), 0);
		cout << "Server:" << buff <<endl;
	}
	
	//��������
	char sendbuf[BUFSIZE] = "�������ǿ�ʼ��������";
	//cin >> sendbuf;
	send(sockClient, sendbuf, sizeof(sendbuf), 0);
	//�������룬Ȼ����
	while(true)
	{
		cin >> sendbuf;
		//cout << "Client:" << sendbuf <<endl;
		send(sockClient, sendbuf, sizeof(sendbuf), 0);
	}
	
	//�ر��׽���
	closesocket(sockClient);
	WSACleanup(); //�ͷų�ʼ��Ws2_32.dll���������Դ
	system("pause");
	return 0;
}
