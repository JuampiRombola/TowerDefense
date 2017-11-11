#ifndef __NEW_LOBBY_GUI_NOTIF__
#define __NEW_LOBBY_GUI_NOTIF__

#include <iostream>

#include "GUINotification.h"
#include "../Lobbies/Lobby.h"

class NewLobbyGUINotification : public GUINotification {
private:
	Lobby& _lobby;
public:
	NewLobbyGUINotification(Lobby& lobby);
	~NewLobbyGUINotification();
	void Execute();
};

#endif