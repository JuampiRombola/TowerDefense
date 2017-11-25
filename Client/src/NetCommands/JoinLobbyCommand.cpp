#include "../../include/NetCommands/JoinLobbyCommand.h"
#include "../../../Common/Protocolo.h"

JoinLobbyCommand::JoinLobbyCommand(uint lobbyGUID) : _lobbyGUID(lobbyGUID)
{
	
}

JoinLobbyCommand::~JoinLobbyCommand(){
}



void JoinLobbyCommand::SendCommand(SocketWrapper& sock){
    sock.SendByte(JOIN_LOBBY);
    sock.SendInt32(_lobbyGUID);
}
