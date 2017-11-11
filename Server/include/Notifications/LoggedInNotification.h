#ifndef __LOGGED_IN_NOTIFICATION__
#define __LOGGED_IN_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"

class LoggedInNotification : public Notification 
{

private:
	PlayerProxy& _player;
public:
	LoggedInNotification(PlayerProxy& player);
	~LoggedInNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif