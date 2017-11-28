#ifndef __LOBBY_IS_GONE_NOTIFICATION__
#define __LOBBY_IS_GONE_NOTIFICATION__


class GTKmmRunnerl;

#include <cstdint>
#include "GTKNotification.h"

class LobbyIsGoneGTKNotification : public GTKNotification {
private:
	uint32_t _lobbyGuid;
public:
	LobbyIsGoneGTKNotification(uint32_t lobbyGuid);
	~LobbyIsGoneGTKNotification();
	void Execute(GTKmmRunner& runner);
};

#endif


