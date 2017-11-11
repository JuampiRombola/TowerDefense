#ifndef __NOTIFICATION__
#define __NOTIFICATION__

#include <vector>
#include "../PlayerProxy.h"

class Notification 
{
protected:
	std::vector<PlayerProxy*> _playersToNotify;
public:
	Notification();
	virtual ~Notification();
	virtual void Notify() = 0;
	virtual void SetPlayersToNotify(std::vector<PlayerProxy*>* players) = 0;

};

#endif
