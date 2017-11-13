#ifndef _GAMESTARTED_NOTIFICATION__
#define _GAMESTARTED_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../../include/Lobbies/Lobby.h"

class GameStartedNotification : public Notification
{

private:
	Lobby& _lobby;
public:
	GameStartedNotification(Lobby& lobby);
	~GameStartedNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif