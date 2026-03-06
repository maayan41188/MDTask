#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include "sqlite3.h"
#include "Helper.h"
#include <string>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	void clientHandler(SOCKET clientSock);
	void getSQL();
	void acceptClient();
	static int callback(void* data, int argc, char** argv, char** azColName);
	void addTask(SOCKET clientSocket);
	static int countResults(void* data, int argc, char** argv, char** azColName);
	void getData(SOCKET clientSocket);
	static int getTaskData(void* data, int argc, char** argv, char** colName);
	
	sqlite3* db;
	SOCKET _serverSocket;
};