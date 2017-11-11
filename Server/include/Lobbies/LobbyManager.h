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

class LobbyManager 
{
private:
	std::mutex _lobbiesMutex;
	std::vector<Lobby*> _lobbies;
	uint _lobbyGUID;
	ThreadSafeQueue<Notification*>& _notifications;
	void _CreateNewLobby(std::string& lobbyName);
	void _HandleCreateNewLobby(PlayerProxy& player);
	void _HandleGetLobbies(PlayerProxy& player);
	void _HandleJoinLobby(PlayerProxy& player);
	void _HandleLeaveLobby(PlayerProxy& player);
public:
	LobbyManager(ThreadSafeQueue<Notification*>& notifications);
	~LobbyManager();

	void HandleRequest(PlayerProxy& player);

};

#endif
