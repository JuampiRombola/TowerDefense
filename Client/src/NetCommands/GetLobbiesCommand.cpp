#include <iostream>
#include <sstream>
#include <iomanip>
#include "NetCommands/GetLobbiesCommand.h"
#include "../../Protocolo.h"

GetLobbiesCommand::GetLobbiesCommand() 
{
	
}

GetLobbiesCommand::~GetLobbiesCommand(){
}



void GetLobbiesCommand::SendCommand(SocketWrapper& sock){
	uint8_t opcode = LOBBY_OPCODE; 
	sock.Send((char*) &opcode, 1);
	uint8_t instruction = GET_LOBBIES; 
	sock.Send((char*)&instruction, 1);
}
