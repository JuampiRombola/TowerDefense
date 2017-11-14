#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>

#include "../../include/GameModel/TowerDefenseGame.h"
#include "../../include/GameModel/Map/Map.h"
#include "../../include/GameModel/EnviormentUnits/DemonioVerde.h"
#include "../../include/GameModel/EnviormentUnits/Abmonible.h"
#include "../../include/GameModel/EnviormentUnits/Espectro.h"
#include "../../include/GameModel/EnviormentUnits/NoMuerto.h"
#include "../../include/GameModel/EnviormentUnits/HalconSangriento.h"
#include "../../include/GameModel/EnviormentUnits/HombreCabra.h"
#include "../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../include/GameModel/Towers/Tower.h"
#include "../../include/GameModel/Towers/GroundTower.h"
#include "../../include/GameModel/GameConfiguration.h"
#include "../../include/GameModel/Helpers.h"
#include "../../include/GameModel/GameNotifications/UnitCreatedGameNotification.h"
#include "../../include/GameModel/GameNotifications/GameOverGameNotification.h"

TowerDefenseGame::TowerDefenseGame(uint gameId,
	ThreadSafeQueue<GameNotification*>& notifications, std::vector<PlayerProxy*> playersInGame) :
	_endedMutex(), _commandQueueMutex(), _commands(),_executedCommandQueueMutex(), 
	_executedCommands(), _gameStateMutex(),
	 _gameId(gameId),
	_ended(false), _stopped(false), _steps(0), _enemyIdCounter(0), _units(),
	_map(8, 8, "map.yaml"), notifications(notifications), _players(playersInGame)
{
	std::string ss("config.yaml");
	GameCfg = new GameConfiguration(ss);

//	mv->createTower(1, TORRE_TIERRA, 2, 0);
//	mv->createTower(2, TORRE_AIRE, 2, 2);
//	mv->createTower(3, TORRE_FUEGO, 1, 4);
//	mv->createTower(4, TORRE_AGUA, 4, 6);

	this->QueueCommand(new BuildTowerCommand(Ground, 2, 0));
	this->QueueCommand(new BuildTowerCommand(Air, 2, 2));
	this->QueueCommand(new BuildTowerCommand(Fire, 1, 4));
	this->QueueCommand(new BuildTowerCommand(Water, 4, 6));
}

TowerDefenseGame::~TowerDefenseGame()
{
	this->Stop();

	for (auto it = _units.begin(); it != _units.end(); ++it)
		delete *it;

	delete GameCfg;
}


void TowerDefenseGame::_SpawnEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro uno random :P
	
	static int i = 0;
	i++;
	if (i >= 3)
		return;
	static bool unooelotro = true;
	if (unooelotro){unooelotro=false;return;
		/*uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
		PathTile* spawn = _map.GetRandomSpawnTile();
		uint hombreCabraSpeed = GameCfg->Cfg["units"]["hombre_cabra"]["speed"].as<uint>();
		uint hombreCabraStepDelay_ms = floor(unitbaseStepDelay_ms / hombreCabraSpeed);
		uint hombreCabraHealthPoints = GameCfg->Cfg["units"]["hombre_cabra"]["health_points"].as<uint>();
		EnviormentUnit* unit = new HombreCabra(++_enemyIdCounter, hombreCabraStepDelay_ms, hombreCabraHealthPoints, notifications);
		_units.push_back(unit);
		_map.PlaceUnit(unit, spawn);
		UnitVM vm = unit->GetViewModel();
		std::cout << "UNIT CREATEDDDDD\n" << std::flush;
		notifications.Queue(new UnitCreatedGameNotification(vm, _players));
		unooelotro =false;
		return;*/
	}
	
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint abmoniblespeed = GameCfg->Cfg["units"]["abmonible"]["speed"].as<uint>();
	uint abmoniblestepdelayms = floor(unitbaseStepDelay_ms / abmoniblespeed);
	uint abmonibleshp = GameCfg->Cfg["units"]["abmonible"]["health_points"].as<uint>();
	EnviormentUnit* unit = new Abmonible(++_enemyIdCounter, abmoniblestepdelayms, abmonibleshp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	std::cout << "UNIT CREATEDDDDD\n" << std::flush;
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}


void TowerDefenseGame::QueueCommand(Command* command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.push(command);
}

/*
Command* TowerDefenseGame::GetExecutedCommand(){
	std::lock_guard<std::mutex> lock(_executedCommandQueueMutex);
	if (_executedCommands.size() == 0)
		return nullptr;
	
	Command* c = _executedCommands.front();
	_executedCommands.pop();
	return c;
}*/

EnviormentUnit* TowerDefenseGame::GetUnit(uint id){
	for(auto it = _units.begin(); it != _units.end(); ++it){
		if ((*it)->GetId() == id)
			return *it;
	}
	return nullptr;
}

void TowerDefenseGame::_ExecuteCommands(){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	while (!_commands.empty()){
		Command* c =_commands.front();
		_commands.pop();
		c->Execute(&_map, this, notifications);
		delete c;
	}
}



bool TowerDefenseGame::_Step(){
	static unsigned long long ts = 0;
	unsigned long long actualTs = Helpers::MillisecondsTimeStamp();

	std::lock_guard<std::mutex> gamelock(_gameStateMutex);
	_ExecuteCommands();

	_steps = _steps + 1;

	if (actualTs - ts > 4000){
		ts = actualTs;
		_SpawnEnemy();
	}

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step(*this);
	}

	_map.Step(*this);

	auto it = _units.begin();
	if (it != _units.end()){
		for (; it != _units.end();){
			if (!((*it)->IsAlive())){
				std::cout << "REMOVING DEAD UNIT\n";
				_map.RemoveUnit(*it);
				EnviormentUnit* unit = *it;
				_units.erase(it);
				delete unit;
			} else {
				++it;
			}
		}
	}

	{
		std::lock_guard<std::mutex> lock(_endedMutex);
		std::vector<PathTile*> endTiles = _map.GetFinishTiles();
		for (auto it = endTiles.begin(); it != endTiles.end() && !_ended; ++it){
			_ended = (*it)->HasAnyUnit();
		}
	}

	return !_ended;
}


bool TowerDefenseGame::Ended(){
	std::lock_guard<std::mutex> lock(_endedMutex);
	return _ended;
}

void TowerDefenseGame::Run(){
	_thread = std::thread(&TowerDefenseGame::_Run, this);
}

void TowerDefenseGame::Stop(){
	_stopped = true;
	if (_thread.joinable())
		_thread.join();
}

void TowerDefenseGame::_Run()
{
	static uint clockFrequency = 100;
    std::this_thread::sleep_for (std::chrono::milliseconds(6000));
    unsigned long long lastTimestamp = Helpers::MillisecondsTimeStamp();
	unsigned long long timestamp = 0;
	unsigned long long delta = 0;
	unsigned long long diference = 0;
	while(_Step() && !_stopped) {
		timestamp = Helpers::MillisecondsTimeStamp();
		delta = timestamp - lastTimestamp;
		diference = clockFrequency - delta;

		if (diference >= 0)
			std::this_thread::sleep_for (std::chrono::milliseconds(diference));
		else
			std::cout << "\n\nClock delayed " << diference * -1 << " ms\n\n" << std::flush;
	}

	notifications.Queue(new GameOverGameNotification(_players));
	//
	// Por ahora solo se puede perder.
	// jeje que juego divertido.
	//

	std::cout << "GAME OVER! \n";
}

	std::vector<UnitVM> TowerDefenseGame::GetUnitViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<UnitVM> uVms;
	for (auto it = _units.begin(); it != _units.end(); ++it){
		uVms.push_back((*it)->GetViewModel());
	}
	return uVms;
}


std::vector<ProjectileVM> TowerDefenseGame::GetProjectileViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<Projectile*> projs = _map.GetProjectiles();
	std::vector<ProjectileVM> pVms;
	for (auto it = projs.begin(); it != projs.end(); ++it){
		pVms.push_back((*it)->GetViewModel());
	}
	return pVms;
}

std::vector<TowerVM> TowerDefenseGame::GetTowerViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<TowerVM> t;
	std::vector<Tower*> towers = _map.GetTowers();
	for (auto it = towers.begin(); it != towers.end(); ++it){
		t.push_back((*it)->GetViewModel());
	}
	return t;
}

std::vector<PlayerProxy*> TowerDefenseGame::GetPlayers(){
	return _players;
}


uint TowerDefenseGame::GetID(){
	return _gameId;
}
