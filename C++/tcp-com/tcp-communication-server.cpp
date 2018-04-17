/***************************************************************************
*Copyright (c) 2017,Wuhan
*All rights reserved.
*
*filename: tcp-communication-server.cpp
*description: The server source for tcp communication program.
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
#include <cstdlib>
#include <cstdio>
#pragma comment(lib, "ws2_32.lib")  //����Ws2_32.dll��̬���ӿ��ļ�
#define BUFSIZE 100

using namespace std;

char recvbuf[BUFSIZE];
SOCKET sockconn;

/**
 *��һ���µ��߳������������
 */
DWORD WINAPI recvThread(LPVOID lpParamter)
{
	while(true)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		//��������
		//recv�������������ݣ���һ������Ϊsocket��
		//�ڶ�������Ϊ�������ݻ�����������������Ϊ�������ĳ��ȣ����ĸ�����Ϊ�����ĵ��÷�ʽ��
		recv(sockconn, recvbuf, sizeof(recvbuf), 0);
		cout << "Client:" << recvbuf << endl;
	}
	closesocket(sockconn);
}

int main()
{
	WSADATA wsaData;
	int port = 10800;   //�˿ں�
	//WSAStartup�������ú������ڳ�ʼ��Ws2_32.dll��̬���ӿ⣬
	//��ʹ��socket֮ǰ��һ��Ҫ��ʼ�������ӿ⡣
	//WSAStarup()��һ��������ʾwinsock�İ汾������ʹ�õ���winsock2.2�汾��
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "Winsock��ʼ��ʧ�ܣ�" <<endl;
		return -1;
	}
	
	/**
	 *�������ڼ������׽��֣�������˵�socket
	 */
	//SOCKET socket(int af,int type,int protocol);
	//af:һ����ַ���壬ͨ��ΪAF_INET
	//type:�׽������ͣ�SOCK_STREAM��ʾ�������������ӵ��׽��֡�
	//ΪSOCK_DGRAM����ʾ�������������ӵ����ݰ��׽��֡�ΪSOCK_RAW����ʾ����ԭʼ�׽��֡�
	//protocol:�׽�������Э�飬��ָ����������Ϊ0
	//����ֵ����һ��socket
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	//htons��������һ��16λ�޷��Ŷ������������������з�ʽת��Ϊ�������з�ʽ��htonl����������ǡ���෴��
	addrSrv.sin_port = htons(port);
	/**
     * INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ�������ַ��ʵ�ϱ�ʾ��ȷ����ַ�������е�ַ�����������ַ����
	 * һ����˵���ڸ���ϵͳ�о������Ϊ0ֵ��
     */
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	/**
	 *bind�������ú������ڽ��׽��ְ󶨵�ָ���Ķ˿ں͵�ַ��
	 *��һ������Ϊsocket���ڶ���������һ���ṹָ�룬�������˶˿ں�IP��ַ��Ϣ��
	 *������������ʾ���������ȡ���Ҫ˵�����ǣ��ڶ���������API�б�ʾΪ��const struct sockaddr FAR*,
	 *����﷨�ṹ�һ�û����������˵����Զָ�룬win16ʱ�ڵĲ�����ǳ���ʶ�ˡ�
	 */
	int retVal = bind(sockServer, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if(retVal == SOCKET_ERROR)
	{
		cout << "bindʧ��:" << WSAGetLastError() <<endl;
		return -2;
	}else {
		cout<< "bind�˿ں�IP...ok" <<endl;
	}
	
	/**
	 *listen��������socket����Ϊ����ģʽ������˵�socket���С�
	 *���뽫����˵�socket����Ϊ����ģʽ���ܺͷ���˼������ӡ�
	 *listen()������������������һ������Ϊsocket���ڶ�������Ϊ�ȴ����������еĳ��ȡ�
	 */
	if(listen(sockServer, 10) == SOCKET_ERROR)
	{
		cout << "����ʧ��:" << WSAGetLastError() <<endl;
		return -3;
	}else {
		cout<< "listen port:" << port << "...ok." <<endl;
	}
	
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR_IN);
	
	//�ȴ��ͻ���������
	while(true)
	{
		/*
		 *accept�����������socket���տͻ��˵������������ӳɹ����򷵻�һ��socket��
		 *��socket�����ڷ���˷��ͺͽ������ݡ���һ������Ϊsocket���ڶ�������Ϊ�����ͻ���
		 *�˿�IP��Ϣ��sockaddr_in�ṹָ�룬����������Ϊ���ղ���addr�ĳ��ȡ�
		*/
		sockconn = accept(sockServer, (SOCKADDR*)&addrClient, &len);
		if(sockconn == SOCKET_ERROR)
		{
			cout<<"�ȴ���������ʧ�ܣ�"<<WSAGetLastError() <<endl;
			break;
		} else {
			cout << "���ӽ���..." <<endl;
		}
		
		cout<< "�ͻ���IP��:[" << inet_ntoa(addrClient.sin_addr) << "]" <<endl;
		
		//��������
		char sendbuf[BUFSIZE] = "��ã����Ƿ�����������һ������ɣ�";
		cin >> sendbuf;
		//send�������������ݣ�����Ĳ���������recv()һ����
		int iSend = send(sockconn, sendbuf, sizeof(sendbuf), 0);
		if(iSend == SOCKET_ERROR)
		{
			cout << "��������ʧ�ܣ�" <<endl;
			break;
		}
		
		/*
		HANDLE WINAPI CreateThread(
    		LPSECURITY_ATTRIBUTES   lpThreadAttributes, //�̰߳�ȫ��ص����ԣ�����ΪNULL
    		SIZE_T                  dwStackSize,        //���̵߳ĳ�ʼ��ջ�ڴ�С��������Ϊ0
    		LPTHREAD_START_ROUTINE  lpStartAddress,     //���߳�ִ�еĻص�������Ҳ��Ϊ�̺߳���
    		LPVOID                  lpParameter,        //�����̺߳����Ĳ��������贫�ݲ���ʱΪNULL
    		DWORD                   dwCreationFlags,    //�����̴߳����ı�־
    		LPDWORD                 lpThreadId          //�������������ڻ���߳�ID�����ΪNULL�򲻷����߳�ID
		);
		*/
		HANDLE hThread = CreateThread(NULL, 0, recvThread, NULL, 0, NULL);
		CloseHandle(hThread);
	}
	

	//closesocket�������ر�socket�������Ψһ��һ����������Ҫ�رյ�socket��
	closesocket(sockServer);
	WSACleanup();   //�ͷų�ʼ��Ws2_32.dll���������Դ
	system("pause");
	return 0;
}
