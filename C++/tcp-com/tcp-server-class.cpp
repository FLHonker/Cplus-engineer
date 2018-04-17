#include "server.h"
#include <iostream>
#include <WS2tcpip.h>

using std::cerr;
using std::cout;
using std::endl;

#define SERVER_PORT 5000
#define MSG_BUF_SIZE 1024

Server::Server()
{
    cout << "Initializing server...\n";
    //
    winsock_ver = MAKEWORD(2, 2);
    addr_len = sizeof(SOCKADDR_IN);
    addr_svr.sin_family = AF_INET;
    addr_svr.sin_port = ::htons(SERVER_PORT);
    addr_svr.sin_addr.S_un.S_addr = ADDR_ANY;
    memset(buf_ip, 0, IP_BUF_SIZE);
    //
    ret_val = ::WSAStartup(winsock_ver, &wsa_data);
    if (ret_val != 0)
    {
        cerr << "WSA failed to start up!Error code: " << ::WSAGetLastError() << "\n";
        system("pause");
        exit(1);
    }
    cout << "WSA started up successfully...\n";
    //
    sock_svr = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_svr == INVALID_SOCKET)
    {
        cerr << "Failed to create server socket!Error code: " << ::WSAGetLastError() << "\n";
        ::WSACleanup();
        system("pause");
        exit(1);
    }
    cout << "Server socket created successfully...\n";
    //
    ret_val = ::bind(sock_svr, (SOCKADDR*)&addr_svr, addr_len);
    if (ret_val != 0)
    {
        cerr << "Failed to bind server socket!Error code: " << ::WSAGetLastError() << "\n";
        ::WSACleanup();
        system("pause");
        exit(1);
    }
    cout << "Server socket bound successfully...\n";
    //
    ret_val = ::listen(sock_svr, SOMAXCONN);
    if (ret_val == SOCKET_ERROR)
    {
        cerr << "Server socket failed to listen!Error code: " << ::WSAGetLastError() << "\n";
        ::WSACleanup();
        system("pause");
        exit(1);
    }
    cout << "Server socket started to listen...\n";
    //
    cout << "Server started successfully..." << endl;
}

Server::~Server()
{
    ::closesocket(sock_svr);
    ::closesocket(sock_clt);
    ::WSACleanup();
    cout << "Socket closed..." << endl;
}

DWORD WINAPI CreateClientThread(LPVOID lpParameter);
//
void Server::WaitForClient()
{
    while (true)
    {
        sock_clt = ::accept(sock_svr, (SOCKADDR*)&addr_clt, &addr_len);
        if (sock_clt == INVALID_SOCKET)
        {
            cerr << "Failed to accept client!Error code: " << ::WSAGetLastError() << "\n";
            ::WSACleanup();
            system("pause");
            exit(1);
        }
        ::InetNtop(addr_clt.sin_family, &addr_clt, buf_ip, IP_BUF_SIZE);
        cout << "A new client connected...IP address: " << buf_ip << ", port number: " << ::ntohs(addr_clt.sin_port) << endl;
        h_thread = ::CreateThread(nullptr, 0, CreateClientThread, (LPVOID)sock_clt, 0, nullptr);
        if (h_thread == NULL)
        {
            cerr << "Failed to create a new thread!Error code: " << ::WSAGetLastError() << "\n";
            ::WSACleanup();
            system("pause");
            exit(1);
        }
        ::CloseHandle(h_thread);
    }
}

DWORD WINAPI CreateClientThread(LPVOID lpParameter)
{
    SOCKET sock_clt = (SOCKET)lpParameter;
    char buf_msg[MSG_BUF_SIZE];
    int ret_val = 0;
    int snd_result = 0;
    do 
    {
        memset(buf_msg, 0, MSG_BUF_SIZE);
        ret_val = ::recv(sock_clt, buf_msg, MSG_BUF_SIZE, 0);
        if (ret_val > 0)
        {
            if (strcmp(buf_msg, "exit") == 0)
            {
                cout << "Client requests to close the connection..." << endl;
                break;
            }
            cout << "Message received: " << buf_msg << endl;
            snd_result = ::send(sock_clt, buf_msg, MSG_BUF_SIZE, 0);
            if (snd_result == SOCKET_ERROR)
            {
                cerr << "Failed to send message to client!Error code: " << ::GetLastError() << "\n";
                ::closesocket(sock_clt);
                system("pause");
                return 1;
            }
        }
        else if (ret_val == 0)
        {
            cout << "connection closed..." << endl;
        }
        else
        {
            cerr << "Failed to receive message from client!Error code: " << ::GetLastError() << "\n";
            ::closesocket(sock_clt);
            system("pause");
            return 1;
        }
    } while (ret_val > 0);
    //
    ret_val = ::shutdown(sock_clt, SD_SEND);
    if (ret_val == SOCKET_ERROR)
    {
        cerr << "Failed to shutdown the client socket!Error code: " << ::GetLastError() << "\n";
        ::closesocket(sock_clt);
        system("pause");
        return 1;
    }
    return 0;
}


int main()
{
    Server svr;
    svr.WaitForClient();
    system("pause");
    return 0;
}