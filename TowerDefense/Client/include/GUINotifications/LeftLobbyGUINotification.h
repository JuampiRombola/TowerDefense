#ifndef __LEFT_LOBBY_GUI_NOTIF__
#define __LEFT_LOBBY_GUI_NOTIF__

#include <iostream>
#include <vector>
#include "GUINotifications/GUINotification.h"
#include "Lobbies/Lobby.h"

class LeftLobbyGUINotification : public GUINotification {
private:
	std::vector<Lobby*> _lobbies;
public:
	LeftLobbyGUINotification(std::vector<Lobby*>& lobbies);
	~LeftLobbyGUINotification();
	void Execute();
};

#endif