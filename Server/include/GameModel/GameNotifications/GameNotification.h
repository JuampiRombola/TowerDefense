#ifndef __GAME_NOTIFICATION__
#define __GAME_NOTIFICATION__

#include "../../PlayerProxy.h"

class GameNotification
{
protected:
	std::vector<PlayerProxy*> _playersToNotify;
public:
	GameNotification(std::vector<PlayerProxy*> playersToNotify);
	virtual ~GameNotification();
	virtual void Notify() = 0;

};

#endif
