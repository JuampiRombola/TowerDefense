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
#include "Tower.h"
#include "GroundTower.h"

#include "Exceptions/CannotSpawnWithoutSettingSpawnTilesException.h"


TowerDefenseGame::TowerDefenseGame(uint clockFrequencyMs) : 
	_endedMutex(), _commands(),
	_clockFrequencyMs(clockFrequencyMs),
	_ended(false), _steps(0), _enemyIdCounter(0), 
	_units(), _towers(), _projectiles(),
	_map(10, 10, "jsonmapconfigfilename") 
{

}

TowerDefenseGame::~TowerDefenseGame()
{
	for (auto it = _units.begin(); it != _units.end(); it++)
		delete *it;

	for (auto it = _towers.begin(); it != _towers.end(); it++)
		delete *it;
}


void TowerDefenseGame::_SpawnEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro el primero :P

	PathTile* spawn = _map.GetRandomSpawnTile();
	if (spawn != NULL){
		EnviormentUnit* u = new DemonioVerde(++_enemyIdCounter);
		_units.push_back(u);
		_map.PlaceUnit(u, spawn);
	} else 
		throw new CannotSpawnWithoutSettingSpawnTilesException();

}


void TowerDefenseGame::PlaceGroundTower(uint x, uint y){
	uint GROUNDTOWERCOOLDOWN = 50;
	uint GROUNDTOWERRANGE = 2;


	SolidGroundTile* tile = _map.GetSolidGroundTile(x ,y);
	if (tile != NULL && !tile->HasTower()){
		Tower* t = new GroundTower(GROUNDTOWERCOOLDOWN, GROUNDTOWERRANGE, tile, &_map);
		_towers.push_back(t);
		tile->PlaceTower(t);
		std::cout << "Tower Placed\n";
	}
}


void TowerDefenseGame::QueueCommand(Command& command){

}





bool TowerDefenseGame::_Step(){

	//std::cout << "Step " << _steps << '\n' ;
	_steps = _steps + 1;


	if (_steps == 1){
		_SpawnEnemy();
	}

	for (auto it = _towers.begin(); it != _towers.end(); ++it){
		Projectile* projectile = (*it)->Step();
		if (projectile != NULL){
			_projectiles.push_back(projectile);
		}
	}

	std::vector<Projectile*> toDelete;

	for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it){
		(*it)->Step();
		if ((*it)->Impacted())
			toDelete.push_back((*it));
	}

	for (auto it = toDelete.begin(); it != toDelete.end(); ++it){
		auto it2 = std::find(_projectiles.begin(), _projectiles.end(), *it);
		_projectiles.erase(it2);
		delete *it;
	}

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step();
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