#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Map.h"
#include "IncompletePathException.h"
#include "TileCannotSpawnException.h"
#include "TileIsOutOfBoundsException.h"
#include "PositionAlreadyHasTileException.h"
#include "EnviormentUnit.h"
#include "PathTile.h"

Map::Map(uint rows, uint cols, std::string mapJsonConfig):

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
	PathTile* spawn = new PathTile(0,0);
	PathTile* end = new PathTile(1,1);
	_PlacePathTile(spawn);
	_PlacePathTile(end);
	
	_SetSpawnTile(spawn);

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

void Map::PlaceUnit(EnviormentUnit* unit, PathTile* tile){
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
