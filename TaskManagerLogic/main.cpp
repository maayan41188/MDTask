#include <exception>
#include <iostream>
#include "sqlite3.h"
#include <string>


int main()
{
	sqlite3* db;
	int rc = sqlite3_open("C:\\Users\\Cyber_Magshimim\\Desktop\\Magshimim\\year2\\Tasks\\MDTask\\TaskDataBase.db", &db);

	
	//create a protocol for pipe between GUI and logic
	//java sends add/remove, c++ returns error/success message
	//java sends sort request, c++ steps:
	//insert the tasks into a sorted vector (sorted by the SQL query)
	//
	
	try
	{
		//create socket
		//recieve message from pipe
	}
	catch (const std::exception& e)
	{

	}

}