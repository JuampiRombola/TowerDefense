#ifndef __LOBBY_JOINED_NOTIFICATION__
#define __LOBBY_JOINED_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "Notifications/Notification.h"
#include "PlayerProxy.h"
#include "Lobbies/Lobby.h"
#include "../../Protocolo.h"

class LobbyJoinedNotification : public Notification 
{

private:
	PlayerProxy& _player;
	Lobby& _lobby;
public:
	LobbyJoinedNotification(PlayerProxy& player, Lobby& lobby);
	~LobbyJoinedNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif