#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>
#include <mutex>
#include <queue>
#include <iostream>

#include "Map.h"
#include "EnviormentUnit.h"
#include "Projectile.h"
#include "Command.h"


class TowerDefenseGame{
private:
	std::mutex _endedMutex;

	std::queue<Command> _commands;

	uint _clockFrequencyMs;

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
	TowerDefenseGame(uint clockFrequencyMs);
	~TowerDefenseGame();
	void Run();
	bool Ended();
	void PlaceGroundTower(uint x, uint y);
	void QueueCommand(Command& command);
};

#endif
