#ifndef __GAME_NOTIFICATION__
#define __GAME_NOTIFICATION__

#include "../../PlayerProxy.h"

class GameNotification
{
public:
	GameNotification();
	virtual ~GameNotification();
	virtual void Notify(std::vector<PlayerProxy*> playersToNotify) = 0;

};

#endif
