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
		p->SendByte(ins);
		p->SendInt32(_playerGUID);
		uint32_t lobbyGUID = _lobby.GUID();
		p->SendInt32(lobbyGUID);
	}

}