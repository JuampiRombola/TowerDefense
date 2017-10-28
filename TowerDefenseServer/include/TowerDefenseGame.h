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
#include "GameConfiguration.h"


class TowerDefenseGame{
private:
	std::mutex _endedMutex;
	std::mutex _commandQueueMutex;

	std::queue<Command*> _commands;

	uint _clockFrequencyMs;

	bool _ended;
	uint _steps;	
	uint _enemyIdCounter;

	std::vector<EnviormentUnit*> _units;

	Map _map;
	bool _Step();
	void _SpawnEnemy();
	void _ExecuteCommands();
public:
	TowerDefenseGame(uint clockFrequencyMs, GameConfiguration& gamecfg);
	~TowerDefenseGame();
	void Run();
	bool Ended();
	void QueueCommand(Command* command);
	EnviormentUnit* GetUnit(uint id);
	GameConfiguration& GameCfg;
};

#endif
