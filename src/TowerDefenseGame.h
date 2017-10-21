#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>
#include <iostream>
#include <mutex>

#include "Map.h"
#include "EnviormentUnit.h"

#define CLOCK_FREQUENCY_MS 100

class TowerDefenseGame{
private:
	//Synchronization
	std::mutex _ended_mutex;


	bool _ended;
	unsigned int _steps;	
	unsigned int _enemyIdCounter;
	std::vector<EnviormentUnit*> _units;
	Map _map;
	bool _Step();
public:
	TowerDefenseGame();
	~TowerDefenseGame();
	void SpawnEnemy();
	void Run();
	bool Ended();
};

#endif
