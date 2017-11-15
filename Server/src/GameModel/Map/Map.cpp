#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>

#include "../../../include/GameModel/Map/Map.h"
#include "../../../include/GameModel/Exceptions/IncompletePathException.h"
#include "../../../include/GameModel/Exceptions/TileCannotSpawnException.h"
#include "../../../include/GameModel/Exceptions/TileIsOutOfBoundsException.h"
#include "../../../include/GameModel/Exceptions/PositionAlreadyHasTileException.h"
#include "../../../include/GameModel/Exceptions/NoSetSpawnTilesException.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/TowerDefenseGame.h"
#include "../../../include/GameModel/GameNotifications/ProjectileFiredGameNotification.h"

Map::Map(uint rows, uint cols, std::string mapJsonConfig):
_rows(rows), _cols(cols),
 _tiles(rows * cols), _spawnTiles(), _endTiles(),
_pathTiles(cols, std::vector<PathTile*>(rows)), 
_groundTiles(cols, std::vector<SolidGroundTile*>(rows)),
_projectiles()

{
	for (uint i = 0; i < cols; i++){
		for (uint j = 0; j < rows; j++){
			_pathTiles[i][j] = nullptr;
			_groundTiles[i][j] = nullptr;
		}
	}
	//Armo un camino a mano
    PathTile* path1;
    PathTile* path2;

/*
    PathTile* endMid = new PathTile(0,7, this, nullptr);
    _PlacePathTile(endMid);
    _SetFinishTile(endMid);

    PathTile* path1 = new PathTile(1, 7, this, endMid);
	_PlaceTile(path1);
	PathTile* path2 = new PathTile(2, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(3, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(4, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(5, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(6, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(7, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(8, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(9, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(10, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(11, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(12, 7, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(13, 7, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(14, 7, this, path1);
	_PlaceTile(path2);
	_SetSpawnTile(path2);
*/
    PathTile* endBot = new PathTile(14,3, this, nullptr);
    _PlacePathTile(endBot);
    _SetFinishTile(endBot);

    path1 = new PathTile(13, 3, this, endBot);
	_PlaceTile(path1);
	path2 = new PathTile(12, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(11, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(10, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(9, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(8, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(7, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(6, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(5, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(4, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(3, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(2, 3, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(1, 3, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(0, 3, this, path1);
	_PlaceTile(path2);
	_SetSpawnTile(path2);
/*
    PathTile* endTop = new PathTile(14,3, this, nullptr);
    _PlacePathTile(endTop);
    _SetFinishTile(endTop);
	path1 = new PathTile(13,11, this, endTop);
	_PlaceTile(path1);
	path2 = new PathTile(12, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(11, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(10, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(9, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(8, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(7, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(6, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(5, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(4, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(3, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(2, 11, this, path1);
	_PlaceTile(path2);
	path1 = new PathTile(1, 11, this, path2);
	_PlaceTile(path1);
	path2 = new PathTile(0, 11, this, path1);
	_PlaceTile(path2);
	_SetSpawnTile(path2);*/



	SolidGroundTile* solidGround = new SolidGroundTile(1, 1);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(1, 5);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(1, 9);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(1, 13);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(5, 1);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(5, 5);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(5, 9);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(5, 13);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(9, 1);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(9, 5);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(9, 9);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(9, 13);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(13, 1);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(13, 5);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(13, 9);
	PlaceGroundTile(solidGround);
	solidGround = new SolidGroundTile(13, 13);
	PlaceGroundTile(solidGround);
}


void Map::RemoveUnit(EnviormentUnit* unit){
	unit->GetPosition()->UnitLeave(unit);
}


void Map::PlaceGroundTile(SolidGroundTile* tile){
	if (_groundTiles[tile->GetXPos()][tile->GetYPos()] != nullptr){
		delete tile;
		return;
	}

	_PlaceTile(tile);
	_groundTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlacePathTile(PathTile* tile){
	if (_pathTiles[tile->GetXPos()][tile->GetYPos()] != nullptr){
		delete tile;
		return;
	}
	_PlaceTile(tile);
	_pathTiles[tile->GetXPos()][tile->GetYPos()] = tile;
}

void Map::_PlaceTile(Tile* tile){
	if (tile->GetXPos() >= _cols || tile->GetYPos() >= _rows)
		throw TileIsOutOfBoundsException();

	bool found = false;
	for (auto it = _tiles.begin(); it != _tiles.end(); ++it){

		if (*it == nullptr)
			continue;

		if (tile->GetXPos() == (*it)->GetXPos()){
			if (tile->GetYPos() == (*it)->GetYPos()){
				found = true;
			}
		}
	}

	if (found)
		throw PositionAlreadyHasTileException();

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
		return nullptr;
	return _pathTiles[x][y];
}


void Map::PlaceUnit(EnviormentUnit* unit, PathTile* tile){
	if (tile->CanSpawn()){
		tile->UnitEnter(unit);
		unit->SetPosition(tile, this);
	} else {
		throw TileCannotSpawnException();
	}
}


PathTile* Map::GetRandomSpawnTile(){
	if (_spawnTiles.size() == 0)
		throw NoSetSpawnTilesException();

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % _spawnTiles.size();
	return _spawnTiles[random_variable];
}

SolidGroundTile* Map::GetSolidGroundTile(uint x, uint y){
	if (x >= _cols || y >= _rows)
		return nullptr;
	return _groundTiles[x][y];
}


std::vector<EnviormentUnit*> Map::GetUnitsInRadius(uint range, Tile* tile){

	std::vector<EnviormentUnit*> units;

	std::vector<PathTile*> tilesInRange = GetPathTilesInRange(tile, range);
  //  std::cout << "tiles in range: " << tilesInRange.size() << "\n" << std::flush;

	for (auto it = tilesInRange.begin(); it != tilesInRange.end(); ++it){
		std::vector<EnviormentUnit*> unitsInTile = (*it)->GetUnits();
//        std::cout << "units in tiles in range: " << tilesInRange.size() << "\n" << std::flush;
		for (auto unitIt = unitsInTile.begin(); unitIt != unitsInTile.end(); ++unitIt){
			units.push_back(*unitIt);
		} 
	}

	return units;
}

std::vector<PathTile*> Map::GetFinishTiles(){
	return _endTiles;
}


void Map::_SetSpawnTile(PathTile* tile){
	auto it = std::find(_spawnTiles.begin(), _spawnTiles.end(), tile);
	if (it == _spawnTiles.end()){
		_spawnTiles.push_back(tile);
		tile->SetCanSpawn();
	} 
}

void Map::_SetFinishTile(PathTile* tile){
	auto it = std::find(_endTiles.begin(), _endTiles.end(), tile);
	if (it == _endTiles.end()){
		_endTiles.push_back(tile);
	} 
}

void Map::Step(TowerDefenseGame& game){
	for (auto it = _groundTiles.begin(); it != _groundTiles.end(); ++it){
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			if ((*it2) != nullptr){
				Projectile* p = (*it2)->Step();
				if (p != nullptr){
					_projectiles.push_back(p);
					ProjectileVM vm = p->GetViewModel();
					game.notifications.Queue(new ProjectileFiredGameNotification(vm, game.GetPlayers()));
					std::cout << "TOWER FIRED @x: " << vm.fromXpos << ", @y: " << vm.fromYpos 
                              << ", to x: " << vm.toXpos << ", to y: " << vm.toYpos << " \n" << std::flush;
				}
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

std::vector<PathTile*> Map::GetPathTilesInRange(Tile* tile, uint range){
	std::vector<PathTile*> tiles;
	int x = tile->GetXPos();
	int y = tile->GetYPos();
	std::cout << "x: " << x << ", y: " << y << '\n' << std::flush;
	for (int i = -range; i <= (int) range; i++)
	{
		for (int j = -range; j <= (int) range; j++)
		{
			PathTile* t = GetPathTile(i + x, j + y);
			if (t != nullptr)
				tiles.push_back(t);
		}
	}

	return tiles;
}

std::vector<Projectile*> Map::GetProjectiles(){
	return _projectiles;
}

std::vector<Tower*> Map::GetTowers(){
	std::vector<Tower*> towers;
	for (uint i = 0; i < _cols; i++){
		for (uint j = 0; j < _rows; j++){
			SolidGroundTile* tile = GetSolidGroundTile(i, j);
			if (tile != nullptr){
				Tower* t = tile->GetTower();
				if (t != nullptr)
					towers.push_back(t);
			}
		}
	}
	return towers;
}

/*
PathTile* end = new PathTile(6,6, this, nullptr);
_PlacePathTile(end);
_SetFinishTile(end);

PathTile* p1 = new PathTile(6, 5, this, end);
_PlacePathTile(p1);
PathTile* p2 = new PathTile(5, 5, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(4, 5, this, p2);
_PlacePathTile(p1);
p2 = new PathTile(3, 5, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(2, 5, this, p2);
_PlacePathTile(p1);
p2 = new PathTile(2, 4, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(2, 3, this, p2);
_PlacePathTile(p1);
p2 = new PathTile(3, 3, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(3, 2, this, p2);
_PlacePathTile(p1);
p2 = new PathTile(3, 1, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(2, 1, this, p2);
_PlacePathTile(p1);
p2 = new PathTile(1, 1, this, p1);
_PlacePathTile(p2);
p1 = new PathTile(1, 0, this, p2);
_PlacePathTile(p1);
PathTile* spawn1 = new PathTile(0,0, this, p1);
_PlacePathTile(spawn1);
_SetSpawnTile(spawn1);


SolidGroundTile* solidGround = new SolidGroundTile(2, 0);
PlaceGroundTile(solidGround);

SolidGroundTile* solidGround1 = new SolidGroundTile(2, 2);
PlaceGroundTile(solidGround1);

SolidGroundTile* solidGround2 = new SolidGroundTile(1, 4);
PlaceGroundTile(solidGround2);

SolidGroundTile* solidGround3 = new SolidGroundTile(4, 6);
PlaceGroundTile(solidGround3);

SolidGroundTile* solidGround4 = new SolidGroundTile(3, 4);
PlaceGroundTile(solidGround4);*/