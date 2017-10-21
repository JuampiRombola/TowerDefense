#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>
#include <iostream>
#include <mutex>

#include "Map.h"
#include "EnviormentUnit.h"
#include "Projectile.h"

#define CLOCK_FREQUENCY_MS 100

class TowerDefenseGame{
private:
	//Synchronization
	std::mutex _endedMutex;
	std::mutex _unitsMutex;
	std::mutex _towersMutex;
	std::mutex _projectilesMutex;

	bool _ended;
	unsigned int _steps;	
	unsigned int _enemyIdCounter;

	std::vector<EnviormentUnit*> _units;
	std::vector<Tower*> _towers;
	std::vector<Projectile*> _projectiles;

	Map _map;
	bool _Step();
	void _SpawnEnemy();
public:
	TowerDefenseGame();
	~TowerDefenseGame();
	void Run();
	bool Ended();
	void PlaceGroundTower(uint x, uint y);
};

#endif
