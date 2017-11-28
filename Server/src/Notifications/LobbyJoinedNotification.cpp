#include "../../include/Notifications/LobbyJoinedNotification.h"
#include <iostream>

LobbyJoinedNotification::LobbyJoinedNotification(PlayerProxy& player, Lobby& lobby)
: _player(player), _lobby(lobby) {

}

LobbyJoinedNotification::~LobbyJoinedNotification(){

}

void LobbyJoinedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->GUID() != _player.GUID() && (*it)->state != IN_GAME && ((*it)->state == IN_LOBBY || (*it)->state == BROWSING_LOBBIES )){
			_playersToNotify.push_back(*it);
		}
	}
}

void LobbyJoinedNotification::Notify(){
	uint8_t ins = JOIN_LOBBY;
	uint32_t lobbyGUID = _lobby.GUID();
	_player.SendByte(ins);
	_player.SendInt32(lobbyGUID);
	//recordar que devuelve 0 si nadie eligio fuego.

	uint32_t ready = 0;
    PlayerProxy* p =_lobby.GetFirePlayer();
	if (p != nullptr){
		_player.SendInt32(p->GUID());
		uint8_t ready = _lobby.IsPlayerReady(*p);
		_player.SendByte(ready);
	} else {
		_player.SendInt32(0);
	}


	p =_lobby.GetWaterPlayer();
	if (p != nullptr){
		_player.SendInt32(p->GUID());
		uint8_t ready = _lobby.IsPlayerReady(*p);
		_player.SendByte(ready);
	} else {
		_player.SendInt32(0);
	}

	p =_lobby.GetAirPlayer();
	if (p != nullptr){
		_player.SendInt32(p->GUID());
		uint8_t ready = _lobby.IsPlayerReady(*p);
		_player.SendByte(ready);
	} else {
		_player.SendInt32(0);
	}

	p =_lobby.GetGroundPlayer();
	if (p != nullptr){
		_player.SendInt32(p->GUID());
		uint8_t ready = _lobby.IsPlayerReady(*p);
		_player.SendByte(ready);
	} else {
		_player.SendInt32(0);
	}


	ins = PLAYER_JOINED_LOBBY;
	uint32_t playerGUID = _player.GUID();
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		p->SendByte(ins);
		p->SendInt32(playerGUID);
		p->SendInt32(lobbyGUID);
	}
}