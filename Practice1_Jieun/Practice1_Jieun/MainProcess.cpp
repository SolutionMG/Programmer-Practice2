

#include"pch.h"
#include "BaseServer.h"


int main()
{
	BaseServer baseServer;

	if ( baseServer.Initialize() == false ) 
	{
		std::cout << "baseServer.Initialize() 실패" << std::endl;
		return -1;
	}

	if ( baseServer.Listen() == false )
	{
		std::cout << "baseServer.Listen() 실패" << std::endl;
		return -1;
	}

	if ( baseServer.OpenServer() == false )
	{
		std::cout << "baseServer.OpenServer() 실패" << std::endl;
		return -1;
	}

	return 0;
}