#include "../../include/NetCommands/LeaveLobbyCommand.h"
#include "../../../Common/Protocolo.h"

LeaveLobbyCommand::LeaveLobbyCommand()
{
	
}

LeaveLobbyCommand::~LeaveLobbyCommand(){
	
}



void LeaveLobbyCommand::SendCommand(SocketWrapper& sock){
    sock.SendByte(LEAVE_LOBBY);
}
