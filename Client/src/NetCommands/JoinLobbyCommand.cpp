#include "../../include/NetCommands/JoinLobbyCommand.h"
#include "../../../Common/Protocolo.h"

JoinLobbyCommand::JoinLobbyCommand(uint lobbyGUID) : _lobbyGUID(lobbyGUID)
{
	
}

JoinLobbyCommand::~JoinLobbyCommand(){
}



void JoinLobbyCommand::SendCommand(SocketWrapper& sock){
	uint8_t instruction = JOIN_LOBBY;
	sock.Send((char*)&instruction, 1);
	sock.Send((char*)&_lobbyGUID, 4);
}
