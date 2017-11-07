#include <iostream>
#include "Lobbies/LobbyManager.h"
#include "../../Protocolo.h"
#include "Notifications/SendLobbiesNotification.h"
#include "Notifications/LobbyJoinedNotification.h"
#include "Notifications/LeftLobbyNotification.h"
#include "Exceptions/PlayerStateInLobbyAndHasNoLobbySet.h"


LobbyManager::LobbyManager(ThreadSafeQueue<Notification*>& notifications) 
: _lobbiesMutex(), _lobbies(), _lobbyGUID(0), _notifications(notifications) {
	
}

LobbyManager::~LobbyManager(){
	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		delete (*it);
	}
}

void LobbyManager::HandleRequest(PlayerProxy& player){
	uint8_t opcode;
	player.sock.Recieve((char*) &opcode, 1);
	std::cout << "SERVER LOBBY MANAGER RECIEVED OPCODE: " << (int) opcode << "\n";
	switch( opcode ){
		case CREATE_LOBBY:
			_HandleCreateNewLobby(player);
			break;
		case GET_LOBBIES:
			_HandleGetLobbies(player);
			break;
		case JOIN_LOBBY:
			_HandleJoinLobby(player);
			break;
		case LEAVE_LOBBY:
			_HandleLeaveLobby(player);
			break;
	}
}

void LobbyManager::_HandleLeaveLobby(PlayerProxy& player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);

	if (player.state != IN_LOBBY)
		return;

	if (player.lobby == nullptr)
		throw PlayerStateInLobbyAndHasNoLobbySet();

	player.lobby->PlayerLeave(player);
	player.lobby = nullptr;

	_notifications.Queue(new LeftLobbyNotification(player));
}

void LobbyManager::_HandleJoinLobby(PlayerProxy& player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);
	uint32_t lobbyguid = 1;
	player.sock.Recieve((char*) &lobbyguid, 4);

	if (player.state != BROWSING_LOBBIES)
		return;

	bool found = false;
	bool joined = false;
	Lobby *lobby = nullptr;
	for (auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
		lobby = *it;
		if (lobby->GUID() == lobbyguid){
			found = true;
			joined = lobby->PlayerJoin(player);
		}
	}

	if (joined){
		player.lobby = lobby;
		_notifications.Queue(new LobbyJoinedNotification(player, *lobby));
	}
}


void LobbyManager::_HandleGetLobbies(PlayerProxy& player){
	std::lock_guard<std::mutex> lock(_lobbiesMutex);
	if (player.state != BROWSING_LOBBIES)
		return;

	SendLobbiesNotification* noti = new SendLobbiesNotification(player);

	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		noti->AddLobby(*it);
	}

	_notifications.Queue(noti);
}

void LobbyManager::_HandleCreateNewLobby(PlayerProxy& player){
	uint8_t lobbyNameSize;
	player.sock.Recieve((char*) &lobbyNameSize, 1);

	std::string lobbyName = player.sock.RecieveString(lobbyNameSize);

	if (player.state == BROWSING_LOBBIES){
		_CreateNewLobby(lobbyName);
	}
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