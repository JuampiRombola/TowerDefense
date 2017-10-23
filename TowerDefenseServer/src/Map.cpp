#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <memory>
#include <ctime>

#include "Map.h"
#include "Exceptions/IncompletePathException.h"
#include "Exceptions/TileCannotSpawnException.h"
#include "Exceptions/TileIsOutOfBoundsException.h"
#include "Exceptions/PositionAlreadyHasTileException.h"
#include "Exceptions/NoSetSpawnTilesException.h"
#include "EnviormentUnit.h"
#include "PathTile.h"
#include "Projectile.h"

Map::Map(uint rows, uint cols, std::string mapJsonConfig):
_rows(rows), _cols(cols), _finishTile(std::shared_ptr<PathTile>(nullptr)),
 _tiles(rows * cols), _spawnTiles(), 
_pathTiles(cols, std::vector<std::shared_ptr<PathTile>>(rows)), 
_groundTiles(cols, std::vector<std::shared_ptr<SolidGroundTile>>(rows)),
_projectiles()

{
	for (uint i = 0; i < cols; i++){
		for (uint j = 0; j < rows; j++){
			_pathTiles[i][j] = std::shared_ptr<PathTile>(nullptr);
			_groundTiles[i][j] = std::shared_ptr<SolidGroundTile>(nullptr);
		}
	}
	//Armo un camino a mano
	std::shared_ptr<PathTile> spawn1 = std::shared_ptr<PathTile>(new PathTile(0,0));
	std::shared_ptr<PathTile> spawn2 = std::shared_ptr<PathTile>(new PathTile(0,9));

	_PlacePathTile(spawn1);
	_SetSpawnTile(spawn1);
	_PlacePathTile(spawn2);
	_SetSpawnTile(spawn2);

	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(1,9)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(1,8)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(1,7)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(1,6)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(2,6)));

	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,7)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,8)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(4,8)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(5,8)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(6,8)));

	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(1,0)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(2,0)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,0)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,1)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,2)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,3)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,4)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(4,4)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(5,4)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(6,4)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(6,5)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(6,6)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(6,7)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(7,7)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(8,7)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(8,6)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(8,5)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(8,4)));

	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,5)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(3,6)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(4,6)));
	_PlacePathTile(std::shared_ptr<PathTile>(new PathTile(5,6)));

	std::shared_ptr<PathTile> end = std::shared_ptr<PathTile>(new PathTile(9,4));
	_PlacePathTile(end);

	_PlaceGroundTile(std::shared_ptr<SolidGroundTile>(new SolidGroundTile(2,5)));
	
	_finishTile = end;
}


void Map::RemoveUnit(std::shared_ptr<EnviormentUnit> unit){
	unit.get()->GetPosition()->UnitLeave(unit);
}


void Map::_PlaceGroundTile(std::shared_ptr<SolidGroundTile> tile){
	_PlaceTile(tile);
	_groundTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlacePathTile(std::shared_ptr<PathTile> tile){
	_PlaceTile(tile);
	_pathTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlaceTile(std::shared_ptr<Tile> tile){
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

Map::~Map(){}

std::shared_ptr<PathTile> Map::GetPathTile(uint x, uint y){
	if (x >= _cols || y >= _rows)
		return std::shared_ptr<PathTile>(nullptr);
	return _pathTiles[x][y];
}


void Map::PlaceUnit(std::shared_ptr<EnviormentUnit> unit, std::shared_ptr<PathTile> tile){
	if (tile->CanSpawn()){
		tile->UnitEnter(unit);
		unit->SetPosition(tile, this);
	} else {
		throw new TileCannotSpawnException();
	}
}


std::shared_ptr<PathTile> Map::GetRandomSpawnTile(){
	if (_spawnTiles.size() == 0)
		throw new NoSetSpawnTilesException();

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % _spawnTiles.size();
	return _spawnTiles[random_variable];
}

std::shared_ptr<SolidGroundTile> Map::GetSolidGroundTile(uint x, uint y){
	if (x >= _cols || y >= _rows)
		return std::shared_ptr<SolidGroundTile>(nullptr);
	return _groundTiles[x][y];
}


std::vector<std::shared_ptr<EnviormentUnit>> Map::GetUnitsInRadius(uint range, std::shared_ptr<Tile> tile){
	uint x = tile->GetXPos();
	uint y = tile->GetYPos();
	std::vector<std::shared_ptr<EnviormentUnit>> units;
	std::shared_ptr<PathTile> othertile;
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
//			std::cout << "Checking tile " << i << ", " << j << "\n" << std::flush;
			othertile = _pathTiles[i][j];
			//if (i < (int) _cols && i >= 0){
			//	if (j < (int)_rows && j >= 0){
			//	}
			//}
			
			if (othertile.get() != nullptr){
				std::vector<std::shared_ptr<EnviormentUnit>> unitsInTile = othertile->GetUnits();
				for (auto it = unitsInTile.begin(); it != unitsInTile.end(); ++it)
					units.push_back(*it);
			}
		}
	}

	return units;
}

std::shared_ptr<PathTile> Map::GetFinishTile(){
	return _finishTile;
}


void Map::_SetSpawnTile(std::shared_ptr<PathTile> tile){
	auto it = std::find(_spawnTiles.begin(), _spawnTiles.end(), tile);
	if (it == _spawnTiles.end()){
		_spawnTiles.push_back(tile);
		tile->SetCanSpawn();
	} 
}


void Map::Step(){
	for (auto it = _groundTiles.begin(); it != _groundTiles.end(); ++it){
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			if ((*it2).get() != nullptr){
				std::shared_ptr<Projectile> p = (*it2)->Step();
				if (p.get() != nullptr)
					_projectiles.push_back(p);
			} 
		}
	}

	auto it = _projectiles.begin();
	for (; it != _projectiles.end();){
		(*it)->Step();
		if ((*it)->Impacted())
			_projectiles.erase(it);
		else
			++it;
	}
}