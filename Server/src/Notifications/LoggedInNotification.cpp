#include "../../include/Notifications/LoggedInNotification.h"
#include "../../../Common/Protocolo.h"
#include <iostream>
#include "../../include/Lobbies/Lobby.h"
#include <tuple>

LoggedInNotification::LoggedInNotification(PlayerProxy& player,
										   std::vector<Lobby*>& lobbies,
										   std::vector<std::tuple< uint32_t , uint32_t>>& lobbies2playersGUIDS)
		: _player(player), _lobbies(lobbies), _lobbies2playersGUIDS(lobbies2playersGUIDS) {
	
}

LoggedInNotification::~LoggedInNotification(){
	
}

void LoggedInNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = (*players).begin(); it != (*players).end(); ++it){
		PlayerProxy* p = *it;
		if (p->GUID() != _player.GUID()){
			_playersToNotify.emplace_back(p);
		}
	}
}

void LoggedInNotification::Notify(){
	uint8_t opcode = LOG_IN_SUCCESS;
	_player.sock.Send((char*) &opcode, 1);
	/** Notifico a este jugador acerca de todos los lobbies y jugadores y sus relaciones */

	uint32_t lobbyCount = _lobbies.size();
	_player.sock.Send((char*) &lobbyCount, 4);

	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		uint32_t lobbyGuid = (*it)->GUID();
		std::string name = (*it)->Name();
		_player.sock.Send((char*) &lobbyGuid, 4);
		_player.sock.SendString(name);
	}

	uint32_t playerAmount = _playersToNotify.size();
	_player.sock.Send((char*) &playerAmount, 4);

	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it) {
		uint32_t  playerGuid = (*it)->GUID();
		std::string playerName = (*it)->Name();
		_player.sock.Send((char*) &playerGuid, 4);
		_player.sock.SendString(playerName);
	}

	uint32_t relationsAmount = _lobbies2playersGUIDS.size();
	_player.sock.Send((char*) &relationsAmount, 4);

	for (auto it = _lobbies2playersGUIDS.begin(); it != _lobbies2playersGUIDS.end(); ++it){
		uint32_t lobbyGuid = std::get<0>(*it);
		uint32_t playerGuid = std::get<1>(*it);
		_player.sock.Send((char*) &lobbyGuid, 4);
		_player.sock.Send((char*) &playerGuid, 4);
	}


	/** Notifico a todos los otros jugadores que entro este jugadopr */
	uint8_t otherPlayersOpcode = PLAYER_JOIN;
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		if((*it)->state != DEAD){
			(*it)->sock.Send((char*) &otherPlayersOpcode, 1);
			uint32_t id = _player.GUID();
			(*it)->sock.Send((char*) &id, 4);
			std::string pname = _player.Name();
			(*it)->sock.SendString(pname);
		}
	}
}