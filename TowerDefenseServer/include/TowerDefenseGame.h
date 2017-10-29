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
#include "ViewModels/UnitVM.h"
#include "ViewModels/ProjectileVM.h"
#include "ViewModels/TowerVM.h"


class TowerDefenseGame{
private:
	std::mutex _endedMutex;
	std::mutex _commandQueueMutex;
	std::queue<Command*> _commands;
	std::mutex _executedCommandQueueMutex;
	std::queue<Command*> _executedCommands;

	std::mutex _gameStateMutex;

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

	//encolar un comando para ejecutar, si el comando tiene parametros
	//incorrectos, no altera el estado del juego y no se devolvera
	//en get executed command
	void QueueCommand(Command* command);

	/// Devuelve los  comandos que realmente se ejecutaron y alteraron el estado
	// del juego
	Command* GetExecutedCommand();
	EnviormentUnit* GetUnit(uint id);
	GameConfiguration& GameCfg;

	std::vector<UnitVM> GetUnitViewModels();
	std::vector<ProjectileVM> GetProjectileViewModels();
	std::vector<TowerVM> GetTowerViewModels();
};

#endif
