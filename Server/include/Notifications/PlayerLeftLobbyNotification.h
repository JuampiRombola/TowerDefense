#ifndef __PLAYER_LEFT_LOBBY_NOTIFICATION__
#define __PLAYER_LEFT_LOBBY_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"
#include "../Lobbies/Lobby.h"
#include "../../../Common/Protocolo.h"

class PlayerLeftLobbyNotification : public Notification 
{

private:
	Lobby& _lobby;
	PlayerProxy& _playerThatLeft;
public:
	PlayerLeftLobbyNotification(Lobby& lobby, PlayerProxy& playerThatLeft);
	~PlayerLeftLobbyNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif