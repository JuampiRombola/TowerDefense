#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <memory>
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
}


void TowerDefenseGame::_SpawnEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro uno random :P

	std::shared_ptr<PathTile> spawn = _map.GetRandomSpawnTile();
	std::shared_ptr<EnviormentUnit> unit(new Espectro(++_enemyIdCounter));
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
}


void TowerDefenseGame::QueueCommand(std::shared_ptr<Command> command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.emplace(command);
}



void TowerDefenseGame::_ExecuteCommands(){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	while (!_commands.empty()){
		_commands.front().get()->Execute(&_map);
		_commands.pop();
	}
}



bool TowerDefenseGame::_Step(){

	std::cout << "Tick\n";

	this->_ExecuteCommands();
	

	_steps = _steps + 1;


	if (_units.size() != 5){
		_SpawnEnemy();
	}

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step(*it);
	}

	_map.Step();

	auto it = _units.begin();
	if (it != _units.end()){
		for (; it != _units.end();){
			if (!((*it).get()->IsAlive())){
				_map.RemoveUnit(*it);
				_units.erase(it);
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