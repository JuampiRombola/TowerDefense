#include "../../include/Notifications/LeftLobbyNotification.h"
#include "../../include/Lobbies/Lobby.h"
#include <iostream>

LeftLobbyNotification::LeftLobbyNotification(PlayerProxy& player)
: _player(player){

}

LeftLobbyNotification::~LeftLobbyNotification(){

}

void LeftLobbyNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->GUID() != _player.GUID()){
			_playersToNotify.push_back(*it);
		}
	}
}

void LeftLobbyNotification::Notify(){
	uint8_t ins = LEAVE_LOBBY;
	_player.sock.Send((char*) &ins, 1);
}