#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>

#include "Map.h"
#include "EnviormentUnit.h"

class TowerDefenseGame{
private:
	unsigned int _steps;
	unsigned int _enemyIdCounter;
	std::vector<EnviormentUnit*> _units;
	Map _map;
	void _Step();
public:
	TowerDefenseGame();
	~TowerDefenseGame();
	void NewEnemy();
	void Run();
};

#endif
