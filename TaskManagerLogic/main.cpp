#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	/*Server myServer;
	myServer.clientHandler();*/
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.serve(8924);

	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}

