#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../include/NetCommands/CreateLobbyCommand.h"
#include "../../../Common/Protocolo.h"

CreateLobbyCommand::CreateLobbyCommand(std::string lobbyName) : _lobbyName(lobbyName) 
{
	
}

CreateLobbyCommand::~CreateLobbyCommand(){
}

std::string intToPaddedString(uint x){
	std::ostringstream sCard;
    sCard << std::setfill('0') << std::setw(4) << x;
    return sCard.str();
}

void CreateLobbyCommand::SendCommand(SocketWrapper& sock){
	if (_lobbyName.length() > 255)
		return;
	sock.SendByte(CREATE_LOBBY);
	sock.SendString(_lobbyName);
}
