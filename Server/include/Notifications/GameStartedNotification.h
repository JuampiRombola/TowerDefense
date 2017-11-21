#ifndef _GAMESTARTED_NOTIFICATION__
#define _GAMESTARTED_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../../include/Lobbies/Lobby.h"

class GameStartedNotification : public Notification
{

private:
	Lobby& _lobby;
	uint8_t _sup;
	uint32_t _width;
	uint32_t _height;
public:
	GameStartedNotification(Lobby& lobby, uint8_t sup, uint32_t width, uint32_t height);
	~GameStartedNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif