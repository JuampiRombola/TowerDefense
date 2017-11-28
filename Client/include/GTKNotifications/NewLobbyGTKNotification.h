#ifndef __NEW_LOBBY_GUI_NOTIF__
#define __NEW_LOBBY_GUI_NOTIF__

#include <iostream>

#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"

class NewLobbyGTKNotification : public GTKNotification {
private:
	Lobby& _lobby;
public:
	NewLobbyGTKNotification(Lobby& lobby);
	~NewLobbyGTKNotification();
	void Execute(GTKmmRunner& runner);
};

#endif