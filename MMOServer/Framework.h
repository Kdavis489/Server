#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WIN_32_LEAN_AND_MEAN
#include <WinSock2.h>

#include <iostream>
#include <string>
#include <stdio.h>

typedef SOCKET;
typedef INVLAID_SOCKET;
typedef SOCKET_HANDLE;

class Framework
{
public:
	//network
	bool initSock()
	{
#ifdef _WIN32
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			return false;
		}
#endif
	}
	SOCKET createSock()
	{
		listening = socket(AF_INET, SOCK_STREAM, 0);
#ifdef _WIN32
		if (listening == INVALID_SOCKET)
		{
			std::cerr << "Failed to create socket: " << WSAGetLastError();
			return INVALID_SOCKET;
		}
		return listening;
#endif
	}
	bool connectSock(SOCKET listening, const std::string& ipAddress, int port)
	{
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
		serverAddress.sin_port = htons(port);

		if (connect(listening, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
		{
			std::cerr << "failed to connect to server: " << WSAGetLastError() << std::endl;
			return false;
		}
		return true;
	}
	bool listen(SOCKET listening, int backlog)
	{
		if (listen(listening, backlog) == SOCKET_ERROR)
		{
			std::cerr << "Failed too listen on socket: " << WSAGetLastError();
			return false;
		}
		return true;
	}
	bool bindSock()
	{
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
		serverAddress.sin_port = htons(port);
		if (bind(listening, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
		{
			std::cerr << "Failed to bind socket: " << WSAGetLastError() << std::endl;
			return false;
		}
		return true;
	}
	void closeSock()
	{
#ifdef _WIN32
		closesocket(listening);
#else
		close(listening);
#endif
	}
	SOCKET clientSocket;
	SOCKET ServerSocket;
private:
	SOCKET listening;
	std::string ipAddress = "127.0.0.1";
	int port = 80;
};
#endif
