#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include "sqlite3.h"
#include <string>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	bool getSQL(sqlite3*& DB);
	void acceptClient();

	void clientHandler(SOCKET clientSocket);
	
	
	
	SOCKET _serverSocket;
};