#ifndef __JOINED_LOBBY_NOTIF__
#define __JOINED_LOBBY_NOTIF__

#include <iostream>
#include "../GTKNotifications/GTKNotification.h"
#include "../Lobbies/Lobby.h"
#include <string>
#include <vector>

class JoinedLobbyGUINotification : public GTKNotification {
private:
	Lobby& _lobby;
public:
	JoinedLobbyGUINotification(Lobby& lobby);
	~JoinedLobbyGUINotification();
	void Execute(GTKRunner& runner);
};

#endif