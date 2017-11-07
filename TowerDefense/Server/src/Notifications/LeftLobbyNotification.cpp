#include "Notifications/LeftLobbyNotification.h"

#include <iostream>

LeftLobbyNotification::LeftLobbyNotification(PlayerProxy& player)
: _player(player){

}

LeftLobbyNotification::~LeftLobbyNotification(){

}

void LeftLobbyNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void LeftLobbyNotification::Notify(){


	uint8_t opcode = LOBBY_OPCODE;
	_player.sock.Send((char*) &opcode, 1);	
	uint8_t ins = LEAVE_LOBBY;
	_player.sock.Send((char*) &ins, 1);



}