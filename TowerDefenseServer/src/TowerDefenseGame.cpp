#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>

#include "../include/TowerDefenseGame.h"
#include "../include/Map/Map.h"
#include "../include/EnviormentUnits/DemonioVerde.h"
#include "../include/EnviormentUnits/Abmonible.h"
#include "../include/EnviormentUnits/Espectro.h"
#include "../include/EnviormentUnits/NoMuerto.h"
#include "../include/EnviormentUnits/HalconSangriento.h"
#include "../include/EnviormentUnits/HombreCabra.h"
#include "../include/EnviormentUnits/EnviormentUnit.h"
#include "../include/Towers/Tower.h"
#include "../include/Towers/GroundTower.h"
#include "../include/GameConfiguration.h"
#include "../include/Helpers.h"



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
/*
	uint hombreCabraSpeed = GameCfg.Cfg["units"]["hombre_cabra"]["speed"].as<uint>();
	uint hombreCabraStepDelay_ms = floor(unitbaseStepDelay_ms / hombreCabraSpeed);
	uint hombreCabraHealthPoints = GameCfg.Cfg["units"]["hombre_cabra"]["health_points"].as<uint>();
	EnviormentUnit* hombrecabra = new HombreCabra(++_enemyIdCounter,
												  hombreCabraStepDelay_ms, hombreCabraHealthPoints, notifications);
	_units.push_back(hombrecabra);
	_map.PlaceUnit(hombrecabra, spawn);*/

	uint aboCabraSpeed = GameCfg.Cfg["units"]["abmonible"]["speed"]
			.as<uint>();
	uint aboCabraStepDelay_ms = floor(unitbaseStepDelay_ms / aboCabraSpeed);
	uint aboCabraHealthPoints = GameCfg
			.Cfg["units"]["abmonible"]["health_points"].as<uint>();
	EnviormentUnit* abo = new Abmonible(++_enemyIdCounter,
												  aboCabraStepDelay_ms, aboCabraHealthPoints,
										notifications);
	_units.push_back(abo);
	_map.PlaceUnit(abo, spawn);
/*
	uint demoSpeed = GameCfg.Cfg["units"]["demonio_verde"]["speed"].as<uint>();
	uint demoStepDelay_ms = floor(unitbaseStepDelay_ms / demoSpeed);
	uint demoHealthPoints = GameCfg.Cfg["units"]["demonio_verde"]["health_points"
			""].as<uint>();

	EnviormentUnit* demo = new DemonioVerde(++_enemyIdCounter,
												  demoStepDelay_ms, demoHealthPoints,
											notifications);
	_units.push_back(demo);
	_map.PlaceUnit(demo, spawn);*/
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

	static bool ff = false;
	if (actualTs - ts > 5000 && !ff){
		ts = actualTs;
		_SpawnEnemy();
		ff = true;
	}

	_map.Step();

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step();
	}


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