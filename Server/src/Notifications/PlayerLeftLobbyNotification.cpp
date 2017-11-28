#include "../../include/Notifications/PlayerLeftLobbyNotification.h"

#include <iostream>

PlayerLeftLobbyNotification::PlayerLeftLobbyNotification
(Lobby& lobby, PlayerProxy& playerThatLeft)
: _lobby(lobby), _playerThatLeft(playerThatLeft)

{

}

PlayerLeftLobbyNotification::~PlayerLeftLobbyNotification(){

}

void PlayerLeftLobbyNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	_playersToNotify = *players;
}

void PlayerLeftLobbyNotification::Notify(){
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		if (p != &_playerThatLeft && (p->state == BROWSING_LOBBIES || p->state == IN_LOBBY)){
			p->SendByte(PLAYER_LEFT_LOBBY);
			p->SendInt32(_playerThatLeft.GUID());
			p->SendInt32(_lobby.GUID());	
		}
	}
	
	_playerThatLeft.SendByte(PLAYER_LEFT_LOBBY);
	_playerThatLeft.SendInt32(_playerThatLeft.GUID());
	_playerThatLeft.SendInt32(_lobby.GUID());
	
	
}