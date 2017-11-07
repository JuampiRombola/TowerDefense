#ifndef __CLIENT_LOBBY_MANAGER__
#define __CLIENT_LOBBY_MANAGER__

#include <vector>
#include <string>
#include <mutex>
#include <iostream>

#include "SocketWrapper.h"
#include "GUINotifications/GUINotificationQueue.h"
#include "Lobbies/Lobby.h"

class ClientLobbyManager{
private:
	SocketWrapper& _sock;
	std::vector<Lobby*> _lobbies;
	GUINotificationQueue& _guiNotiQueue;
	Lobby* _joinedLobby;
public:
	ClientLobbyManager(GUINotificationQueue& guiNotiQueue, SocketWrapper& sock);
	~ClientLobbyManager();
	void HandleNotification();
	void _HandleNewLobbyNotification();
	void _HandleGetLobbies();
	void _HandleLobbyJoin();
	void _HandlePlayerLeftLobby();
	void _HandlePlayerJoinedLobby();
	void _HandleLeaveLobby();
};






#endif