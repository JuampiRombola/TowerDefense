#ifndef __GAME_STARTED_NOTIF__
#define __GAME_STARTED_NOTIF__

#include <iostream>
#include "../GTKNotifications/GTKNotification.h"
#include <string>
#include <vector>

class GameStartedGTKNotification : public GTKNotification {
private:
	uint8_t _sup;
	uint32_t _width;
	uint32_t _height;
public:
	GameStartedGTKNotification(uint8_t sup, uint32_t width, uint32_t height);
	~GameStartedGTKNotification();
	void Execute(GTKRunner& runner);
};

#endif


