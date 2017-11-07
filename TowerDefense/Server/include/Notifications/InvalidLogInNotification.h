#ifndef __INVALID_LOG_IN_NOTIFICATION__
#define __INVALID_LOG_IN_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "Notifications/Notification.h"
#include "PlayerProxy.h"

class InvalidLogInNotification : public Notification 
{

private:
	PlayerProxy& _player;
public:
	InvalidLogInNotification(PlayerProxy& player);
	~InvalidLogInNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif