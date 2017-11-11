#ifndef __LEFT_LOBBY_NOTIFICATION__
#define __LEFT_LOBBY_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"
#include "../../../Common/Protocolo.h"

class LeftLobbyNotification : public Notification 
{

private:
	PlayerProxy& _player;
public:
	LeftLobbyNotification(PlayerProxy& player);
	~LeftLobbyNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif