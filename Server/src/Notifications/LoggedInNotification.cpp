#include "../../include/Notifications/LoggedInNotification.h"
#include "../../../Common/Protocolo.h"
#include <iostream>
#include "../../include/Lobbies/Lobby.h"
#include <tuple>

LoggedInNotification::LoggedInNotification(PlayerProxy& player,
										   std::vector<Lobby*>& lobbies,
										   std::vector<std::tuple< uint32_t , uint32_t>>& lobbies2playersGUIDS,
										   std::vector<std::tuple< std::string , uint32_t>>& mapCfgs)
		: _player(player), _lobbies(lobbies), _lobbies2playersGUIDS(lobbies2playersGUIDS), _mapCfgs(mapCfgs) {
	
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
	_player.SendByte(opcode);
	_player.SendInt32(_player.GUID());
	std::string pname = _player.Name();
	_player.SendString(pname);
	/** Notifico a este jugador acerca de todos los lobbies y jugadores y sus relaciones */

	uint32_t lobbyCount = _lobbies.size();
	_player.SendInt32(lobbyCount);

	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		uint32_t lobbyGuid = (*it)->GUID();
		std::string name = (*it)->Name();
		_player.SendInt32(lobbyGuid);
		_player.SendString(name);
	}

	uint32_t playerAmount = _playersToNotify.size();
	_player.SendInt32(playerAmount);

	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it) {
		uint32_t  playerGuid = (*it)->GUID();
		std::string playerName = (*it)->Name();
		_player.SendInt32(playerGuid);
		_player.SendString(playerName);
	}

	uint32_t relationsAmount = _lobbies2playersGUIDS.size();
	_player.SendInt32(relationsAmount);

	for (auto it = _lobbies2playersGUIDS.begin(); it != _lobbies2playersGUIDS.end(); ++it){
		uint32_t lobbyGuid = std::get<0>(*it);
		uint32_t playerGuid = std::get<1>(*it);
		_player.SendInt32(lobbyGuid);
		_player.SendInt32(playerGuid);
	}

	/** Notifico a este cliente acerca de los mapas disponibles **/
	uint32_t mapsAmount = _mapCfgs.size();
	_player.SendInt32(mapsAmount);
	for (auto it = _mapCfgs.begin(); it != _mapCfgs.end(); ++it){
		std::tuple<std::string, uint32_t> t = *it;
		std::string mapname = std::get<0>(t);
		uint32_t mapid = std::get<1>(t);
		_player.SendInt32(mapid);
		_player.SendString(mapname);
	}



	/** Notifico a todos los otros jugadores que entro este jugadopr */
	uint8_t otherPlayersOpcode = PLAYER_JOIN;
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		if((*it)->state != DEAD){
			(*it)->SendByte(otherPlayersOpcode);
			uint32_t id = _player.GUID();
			(*it)->SendInt32(id);
			std::string pname = _player.Name();
			(*it)->SendString(pname);
		}
	}



}