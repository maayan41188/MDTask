#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>


enum RecieveType
{
	ADD = 101,
	REMOVE = 102,
	SET_COMPLETE = 103,
	GET_DATA = 104,
	EXIT = 105
};

enum SendType
{
	SUCCESS = 200,
	ADD_ERROR = 301,
	REMOVE_ERROR = 302,
	SET_COMPLETE_ERROR = 303,
	GET_DATA_ERROR = 304
};

enum Lengths
{
	CODE = 3,
	NAME_LEN = 2,
	DESC_LEN = 4,
	PRIORITY = 1,
	ID_LEN = 5,
	DATE_ADDED = 10,
	DEADLINE = 10,
	SET_COMPLETE_LEN= 1,
	ERROR_MESSAGE_Len = 2
};

class Helper
{
public:
	static int getMessageTypeCode(SOCKET sc);
	static int getIntPartFromSocket(SOCKET sc, int bytesNum);
	static std::string getStringPartFromSocket(SOCKET sc, int bytesNum);
	static void sendData(SOCKET sc, std::string message);
	//static void send_update_message_to_client(SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users);
	static std::string getPaddedNumber(int num, int digits);

private:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif