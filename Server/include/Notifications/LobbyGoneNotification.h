#ifndef __LOBBY_GONE_NOTIFICATION__
#define __LOBBY_GONE_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../Lobbies/Lobby.h"
#include "../PlayerProxy.h"

class LobbyGoneNotification : public Notification
{

private:
	Lobby& _lobby;
public:
	LobbyGoneNotification(Lobby& lobby);
	~LobbyGoneNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif