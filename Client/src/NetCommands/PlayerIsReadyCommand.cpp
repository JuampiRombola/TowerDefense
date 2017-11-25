#include "../../include/NetCommands/PlayerIsReadyCommand.h"
#include "../../../Common/Protocolo.h"

PlayerIsReadyCommand::PlayerIsReadyCommand()
{
	
}

PlayerIsReadyCommand::~PlayerIsReadyCommand(){
	
}



void PlayerIsReadyCommand::SendCommand(SocketWrapper& sock){
	uint8_t instruction = PLAYER_IS_READY;
    sock.SendByte(instruction);
}
