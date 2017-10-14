#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>
#include <string>
#include <unordered_set>

#include "Map.h"
#include "IEnviormentUnit.h"

class TowerDefenseGame{
private:
	std::unordered_set<IEnviormentUnit*> _units;
	Map _map;
public:
	TowerDefenseGame();
	~TowerDefenseGame();
};

#endif
