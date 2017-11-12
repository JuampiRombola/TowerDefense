#ifndef __JOINED_LOBBY_NOTIF__
#define __JOINED_LOBBY_NOTIF__

#include <iostream>
#include "../GTKNotifications/GTKNotification.h"
#include <string>
#include <vector>

class JoinedLobbyGUINotification : public GTKNotification {
private:
	std::string _lobbyName;
	std::vector<std::string> _playerNames;
public:
	JoinedLobbyGUINotification(std::string lobbyName, std::vector<std::string>& playerNames);
	~JoinedLobbyGUINotification();
	void Execute(GTKRunner& runner);
};

#endif