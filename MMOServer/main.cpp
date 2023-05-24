#include "Framework.h"
int main()
{
	Framework frame;
	if (!frame.initSock())
	{
		std::cerr << " failed" << std::endl;
		return 1;
	}
	if (frame.clientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return 1;
	}

}
