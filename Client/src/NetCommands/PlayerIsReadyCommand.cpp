#include "../../include/NetCommands/PlayerIsReadyCommand.h"
#include "../../../Common/Protocolo.h"

PlayerIsReadyCommand::PlayerIsReadyCommand()
{
	
}

PlayerIsReadyCommand::~PlayerIsReadyCommand(){
	
}



void PlayerIsReadyCommand::SendCommand(SocketWrapper& sock){
    sock.SendByte(PLAYER_IS_READY);
}
