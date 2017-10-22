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

	EnviormentUnit* u = new DemonioVerde(++_enemyIdCounter);
	_units.push_back(u);
	_map.SpawnUnit(u);
}


void TowerDefenseGame::_Step(){
	std::cout << "Step " << _steps << '\n' ;
	_steps = _steps + 1;
	for (auto it = _units.begin(); it != _units.end(); it++){
		(*it)->Step();
		(*it)->PrintDebug();
	}
}

void TowerDefenseGame::Run(){
	char c = 'a';
   	std::cin.get(c);
	while (c != 'q'){
		_Step();
		
		if (c == '+')
			NewEnemy();

		std::cin.get(c);
	}
}