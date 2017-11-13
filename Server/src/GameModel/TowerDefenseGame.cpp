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

TowerDefenseGame::TowerDefenseGame(uint clockFrequencyMs, GameConfiguration& gamecfg,
	ThreadSafeQueue<GameNotification*>& notifications) : 
	_endedMutex(), _commandQueueMutex(), _commands(),_executedCommandQueueMutex(), 
	_executedCommands(), _gameStateMutex(),
	 _clockFrequencyMs(clockFrequencyMs), 
	_ended(false), _steps(0), _enemyIdCounter(0), _units(), 
	_map(10, 10, "jsonmapconfigfilename"), GameCfg(gamecfg), notifications(notifications)
{


}

TowerDefenseGame::~TowerDefenseGame()
{
	for (auto it = _units.begin(); it != _units.end(); ++it)
		delete *it;
}


void TowerDefenseGame::_SpawnEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro uno random :P

	uint unitbaseStepDelay_ms = GameCfg.Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();

	uint hombreCabraSpeed = GameCfg.Cfg["units"]["hombre_cabra"]["speed"].as<uint>();
	uint hombreCabraStepDelay_ms = floor(unitbaseStepDelay_ms / hombreCabraSpeed);
	uint hombreCabraHealthPoints = GameCfg.Cfg["units"]["hombre_cabra"]["health_points"].as<uint>();
	EnviormentUnit* unit = new HombreCabra(++_enemyIdCounter, hombreCabraStepDelay_ms, hombreCabraHealthPoints, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
}


void TowerDefenseGame::QueueCommand(Command* command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.push(command);
}

Command* TowerDefenseGame::GetExecutedCommand(){
	std::lock_guard<std::mutex> lock(_executedCommandQueueMutex);
	if (_executedCommands.size() == 0)
		return nullptr;
	
	Command* c = _executedCommands.front();
	_executedCommands.pop();
	return c;
}

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
		if (c->Execute(&_map, this)){
			std::lock_guard<std::mutex> lock(_executedCommandQueueMutex);
			_executedCommands.push(c);
		}
	}
}



bool TowerDefenseGame::_Step(){
	static unsigned long long ts = 0;
	unsigned long long actualTs = Helpers::MillisecondsTimeStamp();

	std::lock_guard<std::mutex> gamelock(_gameStateMutex);
	_ExecuteCommands();
		
	if (ts == 0) {
		ts = actualTs;
	}


	_steps = _steps + 1;


	if (actualTs - ts > 100 && _units.size() != 100){
		ts = actualTs;
		_SpawnEnemy();
	}

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step();
	}

	_map.Step();

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



void TowerDefenseGame::Run()
{

	unsigned long long lastTimestamp = Helpers::MillisecondsTimeStamp();
	unsigned long long timestamp = 0;
	unsigned long long delta = 0;
	unsigned long long diference = 0;
	while(_Step()) {
		timestamp = Helpers::MillisecondsTimeStamp();
		delta = timestamp - lastTimestamp;
		diference = _clockFrequencyMs - delta;

		if (diference >= 0)
			std::this_thread::sleep_for (std::chrono::milliseconds(diference));
		else
			std::cout << "\n\nClock delayed " << diference * -1 << " ms\n\n" << std::flush;
	}

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