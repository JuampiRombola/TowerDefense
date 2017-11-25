#include "../../include/Notifications/LobbyJoinedNotification.h"
#include <iostream>

LobbyJoinedNotification::LobbyJoinedNotification(PlayerProxy& player, Lobby& lobby)
: _player(player), _lobby(lobby) {

}

LobbyJoinedNotification::~LobbyJoinedNotification(){

}

void LobbyJoinedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->GUID() != _player.GUID() && (*it)->state != IN_GAME){
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


    PlayerProxy* p =_lobby.GetFirePlayer();
	uint32_t firepguid = (p == nullptr) ? 0 : p->GUID();
	_player.SendInt32(firepguid);

    p = _lobby.GetWaterPlayer();
	uint32_t waterpguid = (p == nullptr) ? 0 : p->GUID();
	_player.SendInt32(waterpguid);

    p = _lobby.GetAirPlayer();
	uint32_t airpguid = (p == nullptr) ? 0 : p->GUID();
	_player.SendInt32(airpguid);

    p = _lobby.GetGroundPlayer();
	uint32_t groundpguid = (p == nullptr) ? 0 : p->GUID();
	_player.SendInt32(groundpguid);


	ins = PLAYER_JOINED_LOBBY;
	uint32_t playerGUID = _player.GUID();
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		p->SendByte(ins);
		p->SendInt32(playerGUID);
		p->SendInt32(lobbyGUID);
	}
	
}