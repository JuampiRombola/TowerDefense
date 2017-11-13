#include <iostream>
#include "../../include/Lobbies/LobbyManager.h"
#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/LobbyJoinedNotification.h"
#include "../../include/Notifications/LeftLobbyNotification.h"
#include "../../include/Exceptions/PlayerStateInLobbyAndHasNoLobbySet.h"
#include "../../include/Exceptions/InvalidSpellTypeException.h"
#include "../../include/Notifications/LoggedInNotification.h"


LobbyManager::LobbyManager(ThreadSafeQueue<Notification*>& notifications)
: _lobbiesMutex(), _lobbies(), _lobbyGUID(0), _notifications(notifications) {
	
}

LobbyManager::~LobbyManager(){
	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		delete (*it);
	}
}

void LobbyManager::HandlePlayerIsReady(PlayerProxy &player){
	if (player.lobby == nullptr || player.state != IN_LOBBY)
		return;

	player.lobby->PlayerIsReady(player);
}

void LobbyManager::HandlePlayerPickedSpell(PlayerProxy &player){
	uint8_t spell;
	player.sock.Recieve((char*) &spell, 1);
	SPELL_TYPE type = (SPELL_TYPE )spell;
	switch (type){
		case SPELL_TYPE_WATER:
			player.lobby->PlayerPickWater(player);
			break;
		case SPELL_TYPE_AIR:
			player.lobby->PlayerPickAir(player);
			break;
		case SPELL_TYPE_GROUND:
			player.lobby->PlayerPickGround(player);
			break;
		case SPELL_TYPE_FIRE:
			player.lobby->PlayerPickFire(player);
			break;
		default:
			throw InvalidSpellTypeException();
	}
}
void LobbyManager::HandlePlayerUnpickedSpell(PlayerProxy &player){
	uint8_t spell;
	player.sock.Recieve((char*) &spell, 1);
	SPELL_TYPE type = (SPELL_TYPE )spell;
	switch (type){
		case SPELL_TYPE_WATER:
			player.lobby->PlayerUnpickWater(player);
			break;
		case SPELL_TYPE_AIR:
			player.lobby->PlayerUnpickAir(player);
			break;
		case SPELL_TYPE_GROUND:
			player.lobby->PlayerUnpickGround(player);
			break;
		case SPELL_TYPE_FIRE:
			player.lobby->PlayerUnpickFire(player);
			break;
		default:
			throw InvalidSpellTypeException();
	}
}

void LobbyManager::HandleLogin(PlayerProxy &player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);
	std::cout << " CHECKPOINT2 \n" << std::flush;


	std::vector<Lobby* > lobbies;
	auto lobbies2playersGUIDS = std::vector<std::tuple<uint32_t, uint32_t>>();

	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		uint32_t lobbyGUID = (*it)->GUID();
		lobbies.emplace_back(*it);
		std::vector<int> playersGUIDS = (*it)->GetPlayersGUIDS();
		uint size = playersGUIDS.size();
		for (auto itplayer = playersGUIDS.begin(); itplayer != playersGUIDS.end(); ++itplayer){
			uint32_t playerguid = *itplayer;
			std::tuple<uint32_t , uint32_t > tup = std::tuple<uint32_t , uint32_t >(lobbyGUID, playerguid);
			lobbies2playersGUIDS.emplace_back(tup);
		}
	}

	int debug = lobbies2playersGUIDS.size();

	_notifications.Queue(new LoggedInNotification(player, lobbies, lobbies2playersGUIDS));
	std::cout << " CHECKPOINT2 \n" << std::flush;

}

void LobbyManager::HandleLeaveLobby(PlayerProxy &player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);

	if (player.state != IN_LOBBY)
		return;

	if (player.lobby == nullptr)
		throw PlayerStateInLobbyAndHasNoLobbySet();
	Lobby* lobbyleft = player.lobby;

	player.lobby->PlayerLeave(player);
	player.lobby = nullptr;
}

void LobbyManager::HandleJoinLobby(PlayerProxy &player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);
	uint32_t lobbyguid = 1;
	player.sock.Recieve((char*) &lobbyguid, 4);

	if (player.state != BROWSING_LOBBIES )
		return;

	bool found = false;
	bool joined = false;
	Lobby *lobby = nullptr;
	for (auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
		lobby = *it;
		if (lobby->GUID() == lobbyguid){
			found = true;
		}
	}


	if (lobby->PlayerJoin(player)){
		player.lobby = lobby;
		_notifications.Queue(new LobbyJoinedNotification(player, *lobby));
	}
}


void LobbyManager::HandleCreateNewLobby(PlayerProxy &player){
	uint8_t lobbyNameSize;
	std::string lobbyName = player.sock.RecieveString();
	if (player.state == BROWSING_LOBBIES)
		_CreateNewLobby(lobbyName);
}

void LobbyManager::_CreateNewLobby(std::string& lobbyName){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);
	bool found = false;
	for(auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
		if ((*it)->Name() == lobbyName)
			found = true;
	}

	if (!found){
		_lobbies.push_back(new Lobby(lobbyName, ++_lobbyGUID, _notifications));
		Notification* noti = new NewLobbyNotification(*_lobbies.back());
		_notifications.Queue(noti);
		std::cout << "new lobby notification queed \n";
	}

}