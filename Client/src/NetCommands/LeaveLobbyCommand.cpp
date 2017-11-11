#include "NetCommands/LeaveLobbyCommand.h"
#include "../../Protocolo.h"

LeaveLobbyCommand::LeaveLobbyCommand()
{
	
}

LeaveLobbyCommand::~LeaveLobbyCommand(){
	
}



void LeaveLobbyCommand::SendCommand(SocketWrapper& sock){
	uint8_t opcode = LOBBY_OPCODE; 
	sock.Send((char*) &opcode, 1);
	uint8_t instruction = LEAVE_LOBBY; 
	sock.Send((char*)&instruction, 1);
}
