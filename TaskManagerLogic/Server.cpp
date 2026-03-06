#include "server.h"

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

    getSQL();
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	std::cout << "Waiting for client connection request" << std::endl;
	acceptClient();
}

void Server::acceptClient()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__);
	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
    clientHandler(client_socket);
}

void Server::clientHandler(SOCKET clientSock)
{
    
    


    /*std::string query = "SELECT * FROM TASK;";

    std::cout << "STATE OF TABLE BEFORE INSERT" << std::endl;

    sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

    std::string sql("INSERT INTO TASK VALUES(1, 't1', 'task1', 1, 900, 1000);"
        "INSERT INTO TASK VALUES(2, 't2', 'task2', 2, 900, 300);"
        "INSERT INTO TASK VALUES(3, 't3', 'task3', 3, 90, 990);");

    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cout << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    std::cout << "STATE OF TABLE AFTER INSERT" << std::endl;

    sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

    sql = "DELETE FROM TASK WHERE ID = 2;";
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record deleted Successfully!" << std::endl;

    std::cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << std::endl;
    sqlite3_exec(db, query.c_str(), callback, NULL, NULL);*/

    int code = 0;
    try
    {
        while (true)
        {
            code = Helper::getMessageTypeCode(clientSock);
            std::cout << code << std::endl;

            switch (code)
            {
            case ADD:
                addTask(clientSock);
                break;
            case REMOVE:

                break;
            case SET_COMPLETE:

                break;
            case GET_DATA:
                getData(clientSock);
                break;
            case EXIT:
                std::cout << "Client has disconnected." << std::endl;
                break;
            default:
                throw std::exception("Invalid code");
            }

            if (code == EXIT)
            {
                break;
            }

            /*std::string send = std::to_string(code + 1);
            Helper::sendData(clientSock, send);*/
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    sqlite3_close(db);
}


void Server::addTask(SOCKET clientSocket)
{
    int len = Helper::getIntPartFromSocket(clientSocket, NAME_LEN);
    std::string name = Helper::getStringPartFromSocket(clientSocket, len);
    
    len = Helper::getIntPartFromSocket(clientSocket, DESC_LEN);
    std::string desc = Helper::getStringPartFromSocket(clientSocket, len);

    int priority = Helper::getIntPartFromSocket(clientSocket, PRIORITY);
    std::cout << "Name: " << name << ", Desc: " << desc << ", Priority: " << std::to_string(priority) << std::endl;
    /*while (count != 0)
    {
        std::string str = "SELECT * FROM TASK WHERE ID = " + std::to_string(id);
        int exit = sqlite3_exec(db, str.c_str(), Server::countQueries, &count, &messageError);
        if (exit != SQLITE_OK)
        {
            std::string error = std::string("Error Create/Open Table: ") + std::string(messageError);
            sqlite3_free(messageError);
            throw std::exception(error.c_str());
        }
        id++;
    }*/

    /*std::string str = "SELECT MAX(ID) FROM TASK";
    int exit = sqlite3_exec(db, str.c_str(), Server::countResults, &count, &messageError);
    if (exit != SQLITE_OK)
    {
        std::string error = std::string("Error Create/Open Table: ") + std::string(messageError);
        sqlite3_free(messageError);
        throw std::exception(error.c_str());
    }*/
    /*std::string sql("INSERT INTO TASK (ID, NAME, DESCRIPTION, PRIORITY, COMPLETE, CREATIONDATE, DUEDATE) VALUES("+ std::to_string(id) +", '" + name + "', '" + desc + "', " + std::to_string(priority) + ", " +  std::to_string(0) + ", 0, 0); ");
    int exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK)
    {
        std::string error = std::string("Error during insert: ") + std::string(messageError);
        sqlite3_free(messageError);
        throw std::exception(error.c_str());
    }*/

    std::string sql = "INSERT INTO TASK (NAME, DESCRIPTION, PRIORITY, COMPLETE, CREATIONDATE, DUEDATE) VALUES ('"
        + name + "', '"
        + desc + "', "
        + std::to_string(priority) + ", 0, 0, 0);";

    char* messageError = nullptr;
    int exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK)
    {
        std::string error = std::string("Error during insert: ") + std::string(messageError);
        sqlite3_free(messageError);
        throw std::exception(error.c_str());
    }

    sqlite3_int64 id = sqlite3_last_insert_rowid(db);
    if (id > 99999)
    {
        throw std::exception("ID exceeded 99999");
    }
    std::string s = "200" + Helper::getPaddedNumber(id, 5);
    Helper::sendData(clientSocket, s);
}

int Server::countResults(void* data, int argc, char** argv, char** azColName)
{
    (*(int*)data)++;
    return 0;
}

void Server::getData(SOCKET clientSocket)
{
    int id = Helper::getIntPartFromSocket(clientSocket, ID_LEN);
    std::cout << "ID: " << std::to_string(id) << std::endl;

    std::string sql = "SELECT DESCRIPTION, PRIORITY FROM TASK WHERE ID = " + std::to_string(id);
    char* messageError = nullptr;
    int exit = sqlite3_exec(db, sql.c_str(), Server::getTaskData, &clientSocket, &messageError);
    if (exit != SQLITE_OK)
    {
        std::string error = std::string("Error during data gather: ") + std::string(messageError); //add sending error message to client
        sqlite3_free(messageError);
        throw std::exception(error.c_str());
    }
}

int Server::getTaskData(void* data, int argc, char** argv, char** colName)
{
    std::string s = "200" + Helper::getPaddedNumber(std::strlen(argv[0]), DESC_LEN) + std::string(argv[0]) + std::string(argv[1]);
    std::cout << "Task Data: " << s << std::endl;
    Helper::sendData((*(SOCKET*)data), s);
    return 0;
}

void Server::getSQL()
{
    int exit = sqlite3_open("C:\\Users\\Cyber_Magshimim\\Desktop\\Magshimim\\year2\\Tasks\\MDTask\\TaskDataBase.db", &db);

    if (exit)
    {
        /*std::cout << "Error open DB " << sqlite3_errmsg(db) << std::endl;
        return false;*/
        std::string error = std::string("Error opening DB: ") + std::string(sqlite3_errmsg(db));
        throw std::exception(error.c_str());
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS TASK("
        "ID INTEGER PRIMARY KEY     , "
        "NAME           TEXT    NOT NULL, "
        "DESCRIPTION          TEXT     NOT NULL, "
        "PRIORITY            INT     NOT NULL, "
        "COMPLETE            INT     NOT NULL, "
        "CREATIONDATE        INT, "
        "DUEDATE         INT);";
    char* messageError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        sqlite3_free(messageError);
        std::string error = std::string("Error Create/Open Table: ") + std::string(messageError);
        throw std::exception(error.c_str());
    }
}

int Server::callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    std::cout << (const char*)data << std::endl;

    for (i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

