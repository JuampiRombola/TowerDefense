#ifndef __GAME_STARTED_NOTIF__
#define __GAME_STARTED_NOTIF__

#include <iostream>
#include "../GTKNotifications/GTKNotification.h"
#include <string>
#include <vector>

class GameStartedGTKNotification : public GTKNotification {
public:
	GameStartedGTKNotification();
	~GameStartedGTKNotification();
	void Execute(GTKRunner& runner);
};

#endif