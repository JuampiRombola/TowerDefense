#include <string>
#include <iostream>
#include <algorithm>

#include "Map.h"
#include "IncompletePathException.h"
#include "TileCannotSpawnException.h"
#include "EnviormentUnit.h"
#include "PathTile.h"

Map::Map(uint sideLength, std::string mapJsonConfig) 
: _sideLength(sideLength), _spawnTiles(), _pathTiles(), _groundTiles()
{
	//Armo un camino a mano
	PathTile *tile00 = new PathTile(0,0);
	_pathTiles.push_back(tile00);
	PathTile *tile10 = new PathTile(1,0);
	_pathTiles.push_back(tile10);
	PathTile *tile11 = new PathTile(1,1);
	_pathTiles.push_back(tile11);
	PathTile *tile12 = new PathTile(1,2);
	_pathTiles.push_back(tile12);
	PathTile *tile13 = new PathTile(1,3);
	_pathTiles.push_back(tile13);
	PathTile *tile23 = new PathTile(2,3);
	_pathTiles.push_back(tile23);
	PathTile *tile33 = new PathTile(3,3);
	_pathTiles.push_back(tile33);
	PathTile *tile34 = new PathTile(3,4);
	_pathTiles.push_back(tile34);
	PathTile *tile35 = new PathTile(3,5);
	_pathTiles.push_back(tile35);
	
	tile00->SetNextTile(tile10);
	tile10->SetNextTile(tile11);
	tile11->SetNextTile(tile12);
	tile12->SetNextTile(tile13);
	tile13->SetNextTile(tile23);
	tile23->SetNextTile(tile33);
	tile33->SetNextTile(tile34);
	tile34->SetNextTile(tile35);
	
	_SetSpawnTile(tile00);

	_finishTile = tile35;

}

Map::~Map(){

	for (auto it = _pathTiles.begin(); it != _pathTiles.end(); it++)
		delete *it;
	
	for (auto it = _groundTiles.begin(); it != _groundTiles.end(); it++)
		delete *it;
}


void Map::SpawnUnit(EnviormentUnit* unit, PathTile* tile){
	if (tile->CanSpawn()){
		tile->Place(unit);
		unit->SetPosition(tile);
	} else {
		throw new TileCannotSpawnException();
	}
}

std::vector<PathTile*>& Map::SpawnTiles(){
	return _spawnTiles;
}

PathTile* Map::GetFinishTile(){
	return _finishTile;
}


void Map::_SetSpawnTile(PathTile* tile){
	auto it = std::find(_spawnTiles.begin(), _spawnTiles.end(), tile);
	if (it == _spawnTiles.end()){
		_spawnTiles.push_back(tile);
		tile->SetCanSpawn();
	} 
}
