#ifndef __LOBBY_MANAGER__
#define __LOBBY_MANAGER__

#include <vector>

#include "Lobby.h"
#include "../PlayerProxy.h"

#include "../ThreadSafeQueue.h"
#include "../Notifications/Notification.h"
#include "../Lobbies/Lobby.h"
#include "../Notifications/NewLobbyNotification.h"
#include <mutex>
#include <algorithm>
#include <string>
#include <dirent.h>
class LobbyManager 
{
private:
	std::mutex _lobbiesMutex;
	std::vector<Lobby*> _lobbies;
	uint _lobbyGUID;
	ThreadSafeQueue<Notification*>& _notifications;
	std::vector<Configuration*> _mapCfgs;
	void _CreateNewLobby(std::string& lobbyName);
public:
	LobbyManager(ThreadSafeQueue<Notification*>& notifications);
	~LobbyManager();

	void HandleCreateNewLobby(PlayerProxy &player);
	void HandleJoinLobby(PlayerProxy &player);
	void HandleLeaveLobby(PlayerProxy &player);
	void HandleLogin(PlayerProxy &player);
	void HandlePlayerIsReady(PlayerProxy &player);
	void HandlePlayerPickedSpell(PlayerProxy &player);
	//void HandlePlayerUnpickedSpell(PlayerProxy &player);
	void HandlePickMap(PlayerProxy &player);
};

#endif
