#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "IncompletePathException.h"
#include "TileCannotSpawnException.h"
#include "TileIsOutOfBoundsException.h"
#include "PositionAlreadyHasTileException.h"
#include "EnviormentUnit.h"
#include "PathTile.h"

Map::Map(uint rows, uint cols, std::string mapJsonConfig):
_spawnTilesMutex(),
_rows(rows), _cols(cols), _tiles(rows * cols), _spawnTiles(), 
_pathTiles(cols, std::vector<PathTile*>(rows)), 
_groundTiles(cols, std::vector<SolidGroundTile*>(rows))

{
	for (uint i = 0; i < cols; i++){
		for (uint j = 0; j < rows; j++){
			_pathTiles[i][j] = NULL;
			_groundTiles[i][j] = NULL;
		}
	}
	//Armo un camino a mano
	PathTile* spawn1 = new PathTile(0,0);
	PathTile* spawn2 = new PathTile(0,9);

	_PlacePathTile(spawn1);
	_SetSpawnTile(spawn1);
	_PlacePathTile(spawn2);
	_SetSpawnTile(spawn2);

	_PlacePathTile(new PathTile(1,9));
	_PlacePathTile(new PathTile(1,8));
	_PlacePathTile(new PathTile(1,7));
	_PlacePathTile(new PathTile(1,6));
	_PlacePathTile(new PathTile(2,6));

	_PlacePathTile(new PathTile(3,7));
	_PlacePathTile(new PathTile(3,8));
	_PlacePathTile(new PathTile(4,8));
	_PlacePathTile(new PathTile(5,8));
	_PlacePathTile(new PathTile(6,8));

	_PlacePathTile(new PathTile(1,0));
	_PlacePathTile(new PathTile(2,0));
	_PlacePathTile(new PathTile(3,0));
	_PlacePathTile(new PathTile(3,1));
	_PlacePathTile(new PathTile(3,2));
	_PlacePathTile(new PathTile(3,3));
	_PlacePathTile(new PathTile(3,4));
	_PlacePathTile(new PathTile(4,4));
	_PlacePathTile(new PathTile(5,4));
	_PlacePathTile(new PathTile(6,4));
	_PlacePathTile(new PathTile(6,5));
	_PlacePathTile(new PathTile(6,6));
	_PlacePathTile(new PathTile(6,7));
	_PlacePathTile(new PathTile(7,7));
	_PlacePathTile(new PathTile(8,7));
	_PlacePathTile(new PathTile(8,6));
	_PlacePathTile(new PathTile(8,5));
	_PlacePathTile(new PathTile(8,4));

	_PlacePathTile(new PathTile(3,5));
	_PlacePathTile(new PathTile(3,6));
	_PlacePathTile(new PathTile(4,6));
	_PlacePathTile(new PathTile(5,6));

	PathTile* end = new PathTile(9,4);
	_PlacePathTile(end);
	
	_finishTile = end;
}


void Map::_PlaceGroundTile(SolidGroundTile* tile){
	_PlaceTile(tile);
	_groundTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlacePathTile(PathTile* tile){
	_PlaceTile(tile);
	_pathTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlaceTile(Tile* tile){
	if (tile->GetXPos() >= _cols || tile->GetYPos() >= _rows)
		throw new TileIsOutOfBoundsException();

	bool found = false;
	for (auto it = _tiles.begin(); it != _tiles.end(); ++it){

		if (*it == NULL)
			continue;

		if (tile->GetXPos() == (*it)->GetXPos()){
			if (tile->GetYPos() == (*it)->GetYPos()){
				found = true;
			}
		}
	}

	if (found)
		throw new PositionAlreadyHasTileException();

	_tiles.push_back(tile);

}

Map::~Map(){
	for (auto it = _tiles.begin(); it != _tiles.end(); ++it)
		delete *it;
}

PathTile* Map::GetPathTile(uint x, uint y){
	if (x >= _cols || y >= _rows)
		return NULL;
	return _pathTiles[x][y];
}


void Map::PlaceUnit(EnviormentUnit* unit, PathTile* tile){
	if (tile->CanSpawn()){
		tile->UnitEnter(unit);
		unit->SetPosition(tile, this);
	} else {
		throw new TileCannotSpawnException();
	}
}


PathTile* Map::GetRandomSpawnTile(){
	std::lock_guard<std::mutex> lock(_spawnTilesMutex);
	if (_spawnTiles.size() == 0)
		return NULL;

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % _spawnTiles.size();
	return _spawnTiles[random_variable];
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
