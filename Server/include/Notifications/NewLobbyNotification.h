#ifndef __NEW_LOBBY_NOTIFICATION__
#define __NEW_LOBBY_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../Lobbies/Lobby.h"
#include "../PlayerProxy.h"

class NewLobbyNotification : public Notification 
{

private:
	Lobby& _lobby;
public:
	NewLobbyNotification(Lobby& lobby);
	~NewLobbyNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif