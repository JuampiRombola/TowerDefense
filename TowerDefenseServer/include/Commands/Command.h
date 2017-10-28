#ifndef _COMMAND_
#define _COMMAND_

class Map;
class TowerDefenseGame;

class Command {
public:
	Command();
	virtual ~Command();
	virtual void Execute(Map* map, TowerDefenseGame* game) = 0;
};

#endif