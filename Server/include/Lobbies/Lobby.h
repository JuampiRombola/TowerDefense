#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <mutex>
#include "Lobby.h"
#include "../PlayerProxy.h"
#include "../ThreadSafeQueue.h"
#include "../Notifications/Notification.h"

class Lobby 
{
private:
	std::mutex _playersMutex;
	uint _guid;
	std::string _name;
	std::vector<PlayerProxy*> _players;	
	ThreadSafeQueue<Notification*>& _notifications;

public:
	Lobby(std::string name, uint guid, ThreadSafeQueue<Notification*>& notifications);
	~Lobby();
	std::string Name();
	uint GUID();
	bool PlayerJoin(PlayerProxy& player);
	void PlayerLeave(PlayerProxy& player);
};

#endif
