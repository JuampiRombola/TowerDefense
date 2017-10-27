#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>

#include "Map/Map.h"
#include "Exceptions/IncompletePathException.h"
#include "Exceptions/TileCannotSpawnException.h"
#include "Exceptions/TileIsOutOfBoundsException.h"
#include "Exceptions/PositionAlreadyHasTileException.h"
#include "Exceptions/NoSetSpawnTilesException.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"
#include "Towers/Projectile.h"

Map::Map(uint rows, uint cols, std::string mapJsonConfig):
_rows(rows), _cols(cols), _finishTile(nullptr),
 _tiles(rows * cols), _spawnTiles(), 
_pathTiles(cols, std::vector<PathTile*>(rows)), 
_groundTiles(cols, std::vector<SolidGroundTile*>(rows)),
_projectiles()

{
	for (uint i = 0; i < cols; i++){
		for (uint j = 0; j < rows; j++){
			_pathTiles[i][j] = NULL;
			_groundTiles[i][j] = NULL;
		}
	}
	//Armo un camino a mano
	PathTile* spawn1 = new PathTile(0,0, this);
	PathTile* spawn2 = new PathTile(0,9, this);

	_PlacePathTile(spawn1);
	_SetSpawnTile(spawn1);
	_PlacePathTile(spawn2);
	_SetSpawnTile(spawn2);

	_PlacePathTile(new PathTile(1,9, this));
	_PlacePathTile(new PathTile(1,8, this));
	_PlacePathTile(new PathTile(1,7, this));
	_PlacePathTile(new PathTile(1,6, this));
	_PlacePathTile(new PathTile(2,6, this));

	_PlacePathTile(new PathTile(3,7, this));
	_PlacePathTile(new PathTile(3,8, this));
	_PlacePathTile(new PathTile(4,8, this));
	_PlacePathTile(new PathTile(5,8, this));
	_PlacePathTile(new PathTile(6,8, this));

	_PlacePathTile(new PathTile(1,0, this));
	_PlacePathTile(new PathTile(2,0, this));
	_PlacePathTile(new PathTile(3,0, this));
	_PlacePathTile(new PathTile(3,1, this));
	_PlacePathTile(new PathTile(3,2, this));
	_PlacePathTile(new PathTile(3,3, this));
	_PlacePathTile(new PathTile(3,4, this));
	_PlacePathTile(new PathTile(4,4, this));
	_PlacePathTile(new PathTile(5,4, this));
	_PlacePathTile(new PathTile(6,4, this));
	_PlacePathTile(new PathTile(6,5, this));
	_PlacePathTile(new PathTile(6,6, this));
	_PlacePathTile(new PathTile(6,7, this));
	_PlacePathTile(new PathTile(7,7, this));
	_PlacePathTile(new PathTile(8,7, this));
	_PlacePathTile(new PathTile(8,6, this));
	_PlacePathTile(new PathTile(8,5, this));
	_PlacePathTile(new PathTile(8,4, this));

	_PlacePathTile(new PathTile(3,5, this));
	_PlacePathTile(new PathTile(3,6, this));
	_PlacePathTile(new PathTile(4,6, this));
	_PlacePathTile(new PathTile(5,6, this));

	PathTile* end = new PathTile(9,4, this);
	_PlacePathTile(end);

	PlaceGroundTile(new SolidGroundTile(2,5));
	
	_finishTile = end;


	for (uint i = 0; i < _cols; i++)
	{
		for (uint j = 0; j < _rows; j++)
		{
			PathTile* tile = GetPathTile(i, j);
			if (tile != nullptr){
				tile->InitPossiblePaths();
			}
		}
	}
}


void Map::RemoveUnit(EnviormentUnit* unit){
	unit->GetPosition()->UnitLeave(unit);
}


void Map::PlaceGroundTile(SolidGroundTile* tile){
	if (_groundTiles[tile->GetXPos()][tile->GetYPos()] != NULL){
		delete tile;
		return;
	}

	_PlaceTile(tile);
	_groundTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlacePathTile(PathTile* tile){
	if (_pathTiles[tile->GetXPos()][tile->GetYPos()] != NULL){
		delete tile;
		return;
	}
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

Map::~Map()
{
	for (auto it = _tiles.begin(); it != _tiles.end(); ++it){
		delete (*it);
	}
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
	if (_spawnTiles.size() == 0)
		throw new NoSetSpawnTilesException();

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % _spawnTiles.size();
	return _spawnTiles[random_variable];
}

SolidGroundTile* Map::GetSolidGroundTile(uint x, uint y){
	if (x >= _cols || y >= _rows)
		return NULL;
	return _groundTiles[x][y];
}


std::vector<EnviormentUnit*> Map::GetUnitsInRadius(uint range, Tile* tile){
	uint x = tile->GetXPos();
	uint y = tile->GetYPos();
	std::vector<EnviormentUnit*> units;
	PathTile* othertile;
	int imin = x - range;
	int jmin = y - range;
	int itop = x + range;
	int jtop = y + range;

	if (imin < 0) imin = 0;
	if (jmin < 0) jmin = 0;

	if (itop >= (int) _cols) itop = _cols;
	if (jtop >= (int) _rows) jtop = _rows;


	for (int i = imin; i < itop; i++)
	{
		for (int j = jmin; j < jtop; j++)
		{
			othertile = _pathTiles[i][j];
			if (othertile != NULL){
				std::vector<EnviormentUnit*> unitsInTile = othertile->GetUnits();
				for (auto it = unitsInTile.begin(); it != unitsInTile.end(); ++it)
					units.push_back(*it);
			}
		}
	}

	return units;
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


void Map::Step(){
	for (auto it = _groundTiles.begin(); it != _groundTiles.end(); ++it){
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			if ((*it2) != nullptr){
				Projectile* p = (*it2)->Step();
				if (p != NULL)
					_projectiles.push_back(p);
			} 
		}
	}

	auto it = _projectiles.begin();
	for (; it != _projectiles.end();){
		(*it)->Step();
		if ((*it)->Impacted()){
			Projectile* proj = *it;
			_projectiles.erase(it);
			delete proj;
		}
		else
			++it;
	}
}

std::vector<PathTile*> Map::GetTilesInRange(PathTile* tile, uint range){
	std::vector<PathTile*> tiles;
	int x = tile->GetXPos();
	int y = tile->GetYPos();

	for (int i = -range; i <= (int) range; ++i)
	{
		for (int j = -range; j <= (int) range; ++j)
		{
			PathTile* t = GetPathTile(i + x, j + y);
			if (t != NULL)
				tiles.push_back(t);
		}
	}

	return tiles;
}