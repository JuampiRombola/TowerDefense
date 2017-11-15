#include "../../include/Notifications/LobbyJoinedNotification.h"
#include <iostream>

LobbyJoinedNotification::LobbyJoinedNotification(PlayerProxy& player, Lobby& lobby)
: _player(player), _lobby(lobby) {

}

LobbyJoinedNotification::~LobbyJoinedNotification(){

}

void LobbyJoinedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->GUID() != _player.GUID()){
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
	uint32_t firepguid =_lobby.GetFirePlayerID();
	_player.SendInt32(firepguid);
	uint32_t waterpguid =_lobby.GetWaterPlayerID();
	_player.SendInt32(waterpguid);
	uint32_t airpguid =_lobby.GetAirPlayerID();
	_player.SendInt32(airpguid);
	uint32_t groundpguid =_lobby.GetGroundPlayerID();
	_player.SendInt32(groundpguid);


	ins = PLAYER_JOINED_LOBBY;
	uint32_t playerGUID = _player.GUID();
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		(*it)->SendByte(ins);
		(*it)->SendInt32(playerGUID);
		(*it)->SendInt32(lobbyGUID);
	}


	/*
	uint8_t amount = _playersToNotify.size();
	_player.Send((char*) &amount, 1);

	std::cout << "SENDING PLAYERS IN LOBBY \n";
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){

		/// Notifico al jugador que se unio todos los players que tiene en el lobby
		PlayerProxy* p = *it;
		uint32_t pguid = p->GUID();
		_player.Send((char*) &pguid, 4);
		std::string pname = p->Name();
		uint8_t pnamesizebuf = pname.length();
		_player.Send((char*) &pnamesizebuf, 1);
		_player.Send(pname.c_str(), pname.length());

		// Notifico a cada jugador del lobby que un player se unio
		uint8_t ins2 = PLAYER_JOINED_LOBBY;
		p->sock.Send((char*) &ins2, 1);
		uint32_t pGUID = _player.GUID();
		p->sock.Send((char*) &pGUID, 4);
		std::string playername = _player.Name();
		uint8_t pnameSz = playername.length();
		p->sock.Send((char*) &pnameSz, 1);
		p->sock.Send(playername.c_str(), pnameSz);

	}*/



}