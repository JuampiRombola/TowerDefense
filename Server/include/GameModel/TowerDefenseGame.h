#ifndef _TOWER_DEFENSE_GAME_
#define _TOWER_DEFENSE_GAME_

#include <vector>
#include <mutex>
#include <queue>
#include <iostream>
#include <thread>

#include "Map/Map.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "Towers/Projectile.h"
#include "Commands/Command.h"
#include "Configuration.h"
#include "ViewModels/UnitVM.h"
#include "ViewModels/ProjectileVM.h"
#include "ViewModels/TowerVM.h"
#include "GameNotifications/GameNotification.h"
#include "../ThreadSafeQueue.h"
#include "ClientCooldownManager.h"
#include "Hordes/HordeManager.h"

class TowerDefenseGame{
private:
	std::mutex _gameStartMutex;
	std::condition_variable _gameStartCondVariable;
	bool _canGameStart;


	std::mutex _endedMutex;
	std::mutex _commandQueueMutex;
	std::queue<Command*> _commands;
	std::mutex _executedCommandQueueMutex;
	std::queue<Command*> _executedCommands;
	std::mutex _gameStateMutex;
	uint _gameId;
	bool _ended;
	bool _stopped;
	uint _steps;	
	uint _enemyIdCounter;
	std::vector<EnviormentUnit*> _units;

	Map _map;
	std::thread _thread;
	bool _Step();
	void _SpawnRandomEnemy();
	void _ExecuteCommands();
	void _Run();


	PlayerProxy* _waterPlayer;
	PlayerProxy* _airPlayer;
	PlayerProxy* _firePlayer;
	PlayerProxy* _groundPlayer;

	std::vector<PlayerProxy*> _players;
	std::vector<PlayerProxy*> _ingamePlayers;
	HordeManager _hordeManager;


public:
	TowerDefenseGame(uint gameId, ThreadSafeQueue<GameNotification*>& notifications,
					 std::vector<PlayerProxy*> _players, Configuration& mapCfg);
	~TowerDefenseGame();
	void Run(PlayerProxy* fireplayer, PlayerProxy* airplayer,
			 PlayerProxy* waterplayer, PlayerProxy* groundplayer);
	void Stop();
	bool Ended();

	//encolar un comando para ejecutar, si el comando tiene parametros
	//incorrectos, no altera el estado del juego y no se devolvera
	//en get executed command
	void QueueCommand(Command* command);

	/// Devuelve los  comandos que realmente se ejecutaron y alteraron el estado
	// del juego
	Command* GetExecutedCommand();
	EnviormentUnit* GetUnit(uint id);
	Configuration* GameCfg;
	ThreadSafeQueue<GameNotification*>& notifications;

	std::vector<UnitVM> GetUnitViewModels();
	std::vector<ProjectileVM> GetProjectileViewModels();
	std::vector<TowerVM> GetTowerViewModels();
	std::vector<PlayerProxy*> GetPlayers();

	uint GetID();
	void HandleClientSpellCommand(PlayerProxy& player, CAST_SPELL_TYPE spelltype, uint32_t x, uint32_t y );
	void HandleClientBuildTowerCommand(PlayerProxy& player, SPELL_TYPE spelltype, uint32_t x, uint32_t y );
	void HandleClientUpgradeTowerCommand(uint x, uint y, UpgradeType type);

	void PlayerLoadedGame(PlayerProxy& player);
	void SendMapToPlayer(PlayerProxy& player);

	void ChatMessageFrom(PlayerProxy& player);

    EnviormentUnit* SpawnAbmonible();
	EnviormentUnit* SpawnHombreCabra();
	EnviormentUnit* SpawnHalconSangriento();
	EnviormentUnit* SpawnDemonioVerde();
	EnviormentUnit* SpawnNoMuerto();
	EnviormentUnit* SpawnEspectro();

    void PlayersWon();
	ClientCooldownManager* clientCooldownManager;



};

#endif
