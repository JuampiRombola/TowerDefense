#include <iostream>
#include <thread>

#include "../include/TFServer.h"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;

	//TFServer* tfsv = new TFServer(*(argv + 1));
	TFServer tfsv(*(argv + 1));

	if (!tfsv.ReadyToAcceptConnections()){
		std::cout << " NOT READY \n " << std::flush;
		return 0;
	}

    tfsv.RunServer();

    std::cout << "TOWER DEFENSE SERVER RUNNING...\n" ;

    char c = 0;
    while (c != 'q') std::cin.get(c);

    tfsv.Stop();
    return 0;
}
