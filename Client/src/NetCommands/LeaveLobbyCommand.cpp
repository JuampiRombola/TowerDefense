#include "../../include/NetCommands/LeaveLobbyCommand.h"
#include "../../../Common/Protocolo.h"

LeaveLobbyCommand::LeaveLobbyCommand()
{
	
}

LeaveLobbyCommand::~LeaveLobbyCommand(){
	
}



void LeaveLobbyCommand::SendCommand(SocketWrapper& sock){
	uint8_t instruction = LEAVE_LOBBY;
    sock.SendByte(instruction);
}
