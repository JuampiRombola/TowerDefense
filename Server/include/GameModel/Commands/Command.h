#ifndef _COMMAND_
#define _COMMAND_

#include "../GameNotifications/GameNotification.h"
#include "../../ThreadSafeQueue.h"

class Map;
class TowerDefenseGame;
struct CommandVM;

class Command {
public:
	Command();

	virtual ~Command();

	virtual bool Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications) = 0;
	//virtual CommandVM GetViewModel() = 0;
};

#endif