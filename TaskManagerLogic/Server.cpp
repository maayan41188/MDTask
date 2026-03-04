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
    clientHandler(_serverSocket);
}

void Server::clientHandler(SOCKET clientSocket)
{
    sqlite3* db;
    if (!getSQL(db))
    {
        return;
    }


    try
    {

    }
    catch (const std::exception& e)
    {

    }

    sqlite3_close(db);
}


bool Server::getSQL(sqlite3*& db)
{
    int exit = sqlite3_open("C:\\Users\\Cyber_Magshimim\\Desktop\\Magshimim\\year2\\Tasks\\MDTask\\TaskDataBase.db", &db);

    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS TASK("
        "ID INT PRIMARY KEY     NOT NULL, "
        "NAME           TEXT    NOT NULL, "
        "DESC          TEXT     NOT NULL, "
        "PRIORITY            INT     NOT NULL, "
        "CREATIONDATE        CHAR(50), "
        "DUEDATE         REAL );";
    char* messaggeError;
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        std::cout << "Error Create/Open Table" << std::endl;
        std::cout << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return false;
    }
    return true;
}

int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}