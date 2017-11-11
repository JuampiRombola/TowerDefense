#ifndef _COMMAND_
#define _COMMAND_

class Map;
class TowerDefenseGame;
struct CommandVM;

class Command {
public:
	Command();
	virtual ~Command();
	virtual bool Execute(Map* map, TowerDefenseGame* game) = 0;
	virtual CommandVM GetViewModel() = 0;
};

#endif