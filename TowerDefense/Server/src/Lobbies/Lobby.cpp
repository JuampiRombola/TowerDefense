#include <iostream>
#include <algorithm>
#include "Lobbies/Lobby.h"
#include "Exceptions/PlayerLeftLobbyHeWasntInException.h"
#include "Notifications/PlayerLeftLobbyNotification.h"


Lobby::Lobby(std::string name, uint guid, ThreadSafeQueue<Notification*>& notifications) 
 : _playersMutex(), _guid(guid), _name(name), _players(), _notifications(notifications) {
}

Lobby::~Lobby(){

}

std::string Lobby::Name(){
	return _name;
}

uint Lobby::GUID(){
	return _guid;
}

bool Lobby::PlayerJoin(PlayerProxy& player){
	std::lock_guard<std::mutex> lock(_playersMutex);
	if (_players.size() == 4)
		return false;

	_players.push_back(&player);
	player.state = IN_LOBBY;
	return true;
}

void Lobby::PlayerLeave(PlayerProxy& player){
	std::cout << "PLAYER GUID " << (int) player.GUID() <<  " LEAVING LOBBY\n" << std::flush;
	std::lock_guard<std::mutex> lock(_playersMutex);
	auto it = std::find(_players.begin(), _players.end(), &player);
	PlayerProxy* p = *it;
	if (p == nullptr){
		throw PlayerLeftLobbyHeWasntInException();
	}
	player.state = BROWSING_LOBBIES;
	_players.erase(it);
	_notifications.Queue(new PlayerLeftLobbyNotification(*this, p->GUID()));
}