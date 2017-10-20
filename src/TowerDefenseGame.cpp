#include <iostream>
#include <algorithm>
#include <iterator>

#include "TowerDefenseGame.h"
#include "Map.h"
#include "DemonioVerde.h"
#include "EnviormentUnit.h"

TowerDefenseGame::TowerDefenseGame() : _steps(0), _enemyIdCounter(0), _units(), _map(10, "jsonmapconfigfilename") 
{

}

TowerDefenseGame::~TowerDefenseGame()
{
	for (auto it = _units.begin(); it != _units.end(); it++)
		delete *it;
}


void TowerDefenseGame::NewEnemy(){
	//Por ahora solo tengo demonios verdes.
	//aca iria la logica de que bicho sacar de manera random

	// Para spawnear tiene que haber algun spawntile
	// como lo elegimos el politica del juego
	// por ahora agarro el primero :P


	if (_map.SpawnTiles().begin() == _map.SpawnTiles().end()){
		std::cout << "throw cannot spawn, there are no spawntiles";
	} else {
		PathTile* _spawn = *_map.SpawnTiles().begin();
		EnviormentUnit* u = new DemonioVerde(++_enemyIdCounter);
		_map.SpawnUnit(u, _spawn);
		_units.push_back(u);
	} 
	std::cout << " new enemy created \n";
}


bool TowerDefenseGame::_Step(){
	std::cout << "Step " << _steps << '\n' ;
	_steps = _steps + 1;
	for (auto it = _units.begin(); it != _units.end(); it++){
		(*it)->Step();
		(*it)->PrintDebug();
	}

	return _map.GetFinishTile()->HasAnyUnit();
}




void TowerDefenseGame::Run(){
	char c = 'a';
	bool gameEnded = false;
	while (c != 'q' && !gameEnded){
		std::cin.get(c);

		if (c == '+')
			NewEnemy();

		gameEnded = _Step();
	}
	

	//
	// Por ahora solo se puede perder.
	// jeje que juego divertido.
	//

	std::cout << "GAME OVER!\n";

}