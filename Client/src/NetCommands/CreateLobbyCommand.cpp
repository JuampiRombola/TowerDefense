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
	int lobbyNameSize = _lobbyName.length();
	if (lobbyNameSize > 255)
		return;
	uint8_t opcode = LOBBY_OPCODE; //Para el lobby
	sock.Send((char*) &opcode, 1);
	uint8_t instruction = CREATE_LOBBY; ///New lobby
	sock.Send((char*)&instruction, 1);
	char lobbyNameSizeBuf = (int) _lobbyName.length();
	sock.Send(&lobbyNameSizeBuf, 1);
	sock.Send(_lobbyName.c_str(), _lobbyName.length());
}
