#include <iostream>

#include "TowerDefenseGame.h"
#include "Map.h"
#include "DemonioVerde.h"

TowerDefenseGame::TowerDefenseGame() : _units(), _map(10, "jsonmapconfigfilename") 
{
	IEnviormentUnit* unit = new DemonioVerde();
	_units.emplace(unit);

	_map.DebugPrint();
	_map.SpawnUnit(unit);
}

TowerDefenseGame::~TowerDefenseGame()
{
	
}

