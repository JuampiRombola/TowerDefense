#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <mutex>

#include "TowerDefenseGame.h"
#include "Map.h"
#include "DemonioVerde.h"
#include "EnviormentUnit.h"

#include "CannotSpawnWithoutSettingSpawnTiles.h"


TowerDefenseGame::TowerDefenseGame() : 
 _ended_mutex(), _ended(false), _steps(0), 
 _enemyIdCounter(0), _units(), _map(10, 10, "jsonmapconfigfilename") 
{

}

TowerDefenseGame::~TowerDefenseGame()
{
	for (auto it = _units.begin(); it != _units.end(); it++)
		delete *it;
}


void TowerDefenseGame::SpawnEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro el primero :P


	if (_map.SpawnTiles().begin() != _map.SpawnTiles().end()){
		PathTile* _spawn = *_map.SpawnTiles().begin();
		EnviormentUnit* u = new DemonioVerde(++_enemyIdCounter);
		_map.PlaceUnit(u, _spawn);
		_units.push_back(u);
	} else 
		throw new CannotSpawnWithoutSettingSpawnTiles();

	std::cout << " new enemy created \n";
}


bool TowerDefenseGame::_Step(){
	std::cout << "Step " << _steps << '\n' ;
	_steps = _steps + 1;
	for (auto it = _units.begin(); it != _units.end(); it++){
		(*it)->Step();
		(*it)->PrintDebug();
	}

	
	std::lock_guard<std::mutex> lock(_ended_mutex);
	_ended = _map.GetFinishTile()->HasAnyUnit();
	return !_ended;
}


bool TowerDefenseGame::Ended(){
	std::lock_guard<std::mutex> lock(_ended_mutex);
	return _ended;
}



void TowerDefenseGame::Run()
{
	while(_Step()) 
		std::this_thread::sleep_for (std::chrono::milliseconds(CLOCK_FREQUENCY_MS));

	//
	// Por ahora solo se puede perder.
	// jeje que juego divertido.
	//

	std::cout << "GAME OVER! \n\nPRESS ENTER TO EXIT... \n";
}