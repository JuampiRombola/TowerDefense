#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <mutex>

#include "TowerDefenseGame.h"
#include "Map/Map.h"
#include "EnviormentUnits/DemonioVerde.h"
#include "EnviormentUnits/Abmonible.h"
#include "EnviormentUnits/Espectro.h"
#include "EnviormentUnits/NoMuerto.h"
#include "EnviormentUnits/HalconSangriento.h"
#include "EnviormentUnits/HombreCabra.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "Towers/Tower.h"
#include "Towers/GroundTower.h"
#include "Helpers.h"



TowerDefenseGame::TowerDefenseGame(uint clockFrequencyMs) : 
	_endedMutex(), _commandQueueMutex(), _commands(),
	_clockFrequencyMs(clockFrequencyMs),
	_ended(false), _steps(0), _enemyIdCounter(0), 
	_units(),
	_map(10, 10, "jsonmapconfigfilename") 
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

	PathTile* spawn = _map.GetRandomSpawnTile();
	EnviormentUnit* unit = new Espectro(++_enemyIdCounter);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
}


void TowerDefenseGame::QueueCommand(Command* command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.emplace(command);
}

EnviormentUnit* TowerDefenseGame::GetUnit(uint id){
	for(auto it = _units.begin(); it != _units.end(); ++it){
		if ((*it)->GetId() == id)
			return *it;
	}
	return NULL;
}

void TowerDefenseGame::_ExecuteCommands(){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	while (!_commands.empty()){
		_commands.front()->Execute(&_map, this);
		_commands.pop();
	}
}



bool TowerDefenseGame::_Step(){
	static unsigned long long ts = 0;
	unsigned long long actualTs = Helpers::MillisecondsTimeStamp();


	_ExecuteCommands();
		
	if (ts == 0) {
		ts = actualTs;
	}


	_steps = _steps + 1;


	if (actualTs - ts > 100 && _units.size() != 1){
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

	std::lock_guard<std::mutex> lock(_endedMutex);
	_ended = _map.GetFinishTile()->HasAnyUnit();
	return !_ended;
}


bool TowerDefenseGame::Ended(){
	std::lock_guard<std::mutex> lock(_endedMutex);
	return _ended;
}



void TowerDefenseGame::Run()
{
	while(_Step()) 
		std::this_thread::sleep_for (std::chrono::milliseconds(_clockFrequencyMs));

	//
	// Por ahora solo se puede perder.
	// jeje que juego divertido.
	//

	std::cout << "GAME OVER! \n";
}