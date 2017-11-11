#ifndef __JOINED_LOBBY_NOTIF__
#define __JOINED_LOBBY_NOTIF__

#include <iostream>
#include "GUINotification.h"
#include <string>
#include <vector>

class JoinedLobbyGUINotification : public GUINotification {
private:
	std::string _lobbyName;
	std::vector<std::string> _playerNames;
public:
	JoinedLobbyGUINotification(std::string lobbyName, std::vector<std::string>& playerNames);
	~JoinedLobbyGUINotification();
	void Execute();
};

#endif