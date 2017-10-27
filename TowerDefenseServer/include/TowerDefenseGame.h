#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_



#include <vector>
#include <mutex>
#include <queue>
#include <iostream>

#include "Map/Map.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "Towers/Projectile.h"
#include "Commands/Command.h"


class TowerDefenseGame{
private:
	std::mutex _endedMutex;
	std::mutex _commandQueueMutex;

	std::queue<Command*> _commands;

	uint _clockFrequencyMs;

	bool _ended;
	unsigned int _steps;	
	unsigned int _enemyIdCounter;

	std::vector<EnviormentUnit*> _units;

	Map _map;
	bool _Step();
	void _SpawnEnemy();
	void _ExecuteCommands();
public:
	TowerDefenseGame(uint clockFrequencyMs);
	~TowerDefenseGame();
	void Run();
	bool Ended();
	void QueueCommand(Command* command);
};

#endif
