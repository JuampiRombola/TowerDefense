#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_


#include <memory>
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
	std::mutex _commandQueueMutex;

	std::queue<std::shared_ptr<Command>> _commands;

	uint _clockFrequencyMs;

	bool _ended;
	unsigned int _steps;	
	unsigned int _enemyIdCounter;

	std::vector<std::shared_ptr<EnviormentUnit>> _units;

	Map _map;
	bool _Step();
	void _SpawnEnemy();
	void _ExecuteCommands();
public:
	TowerDefenseGame(uint clockFrequencyMs);
	~TowerDefenseGame();
	void Run();
	bool Ended();
	void QueueCommand(std::shared_ptr<Command> command);
};

#endif
