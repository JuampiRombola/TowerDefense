#include "../../include/Notifications/PlayerLeftLobbyNotification.h"

#include <iostream>

PlayerLeftLobbyNotification::PlayerLeftLobbyNotification
(Lobby& lobby, uint playerGUID)
: _lobby(lobby), _playerGUID(playerGUID) {
}

PlayerLeftLobbyNotification::~PlayerLeftLobbyNotification(){

}

void PlayerLeftLobbyNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		PlayerProxy* p = *it;
		if (p->GUID() != _playerGUID){
			_playersToNotify.push_back(*it);
		}
	}
}

void PlayerLeftLobbyNotification::Notify(){
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		uint8_t ins = PLAYER_LEFT_LOBBY;
		p->sock.Send((char*) &ins, 1);
		p->sock.Send((char*) &_playerGUID, 4);
		uint32_t lobbyGUID = _lobby.GUID();
		p->sock.Send((char*) &lobbyGUID, 4);
	}

}