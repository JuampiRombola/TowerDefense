#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>

#include "../../../../Common/Protocolo.h"
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

Map::Map(uint rows, uint cols, Configuration& mapCfg):
_rows(rows), _cols(cols),
_tiles(rows * cols), _spawnTiles(), _endTiles(),
_pathTiles(rows, std::vector<PathTile*>(cols)),
_groundTiles(rows, std::vector<SolidGroundTile*>(cols)),
_projectiles()

{

	for (uint i = 0; i < rows; i++){
		for (uint j = 0; j < cols; j++){
			_pathTiles[i][j] = nullptr;
			_groundTiles[i][j] = nullptr;
		}
	}


	for (YAML::const_iterator it = mapCfg.Cfg["superficies"].begin();
		 it != mapCfg.Cfg["superficies"].end(); ++it)

	{
		const YAML::Node& node = *it;
		SolidGroundTile* tile = new SolidGroundTile(node["x"].as<uint>(), node["y"].as<uint>());
		PlaceGroundTile(tile);
	}


    std::vector<temp_pathTile> tempPathTiles;

	for (YAML::const_iterator it = mapCfg.Cfg["caminos"].begin();
         it != mapCfg.Cfg["caminos"].end() ; ++it)
	{
        const YAML::Node& node = *it;
        temp_pathTile t;
		t.x = node["x"].as<int>();
		t.y = node["y"].as<int>();
		t.xsig = node["x_sig"].as<int>();
		t.ysig = node["y_sig"].as<int>();
		tempPathTiles.push_back(t);
	}

    PathTile* t = nullptr;
    for (auto it = tempPathTiles.rbegin(); it != tempPathTiles.rend(); ++it ) {
        uint xx = (*it).x;
        uint yy = (*it).y;
		t = new PathTile(xx, yy, this, t);
		_PlacePathTile(t);
    }


	for (YAML::const_iterator it = mapCfg.Cfg["portales"].begin();
		 it != mapCfg.Cfg["portales"].end(); ++it)

	{
		const YAML::Node& node = *it;
		uint x = node["x"].as<uint>();
		uint y = node["y"].as<uint>();
		PathTile* portal = GetPathTile(x, y);
		if (node["tipo"].as<std::string>() == "entrada")
			_SetSpawnTile(portal);
		else
			_SetFinishTile(portal);
	}

}


void Map::RemoveUnit(EnviormentUnit* unit){
	PathTile* u = unit->GetPosition();
    if (u != nullptr)
        u->UnitLeave(unit);
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
	uint x = tile->GetXPos();
	uint y = tile->GetYPos();
	if (_pathTiles[x][y] != nullptr){
		delete tile;
		return;
	}
	_PlaceTile(tile);
	_pathTiles[x][y] = tile;
}

void Map::_PlaceTile(Tile* tile){
	if (tile->GetXPos() >= _rows || tile->GetYPos() >= _cols)
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
	if (x >= _rows || y >= _cols)
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
	if (x >= _rows || y >= _cols)
		return nullptr;
	return _groundTiles[x][y];
}


std::vector<EnviormentUnit*> Map::GetUnitsInRadius(uint range, Tile* tile){

	std::vector<EnviormentUnit*> units;

	std::vector<PathTile*> tilesInRange = GetPathTilesInRange(tile, range);

	for (auto it = tilesInRange.begin(); it != tilesInRange.end(); ++it){
		std::vector<EnviormentUnit*> unitsInTile = (*it)->GetUnits();
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
					game.notifications.Queue(new ProjectileFiredGameNotification(vm));
				}
			} 
		}
	}

	for (auto it = _pathTiles.begin(); it != _pathTiles.end(); ++it){
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			PathTile* p = *it2;
			if (p != nullptr){
				p->Step();
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
	for (uint i = 0; i < _rows; i++){
		for (uint j = 0; j < _cols; j++){
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

bool Map::AreCoordinatesInsideMap(uint x, uint y){
	return (x < _rows && y < _cols);
}

void Map::TransferMapTo(PlayerProxy& player){

	uint8_t mapOpcode = LOAD_MAP;
	uint8_t pathOpcode = PATH_TILE;
	uint8_t strucOpcode = STRUCTURE_TILE;
	uint8_t spawnOpcode = SPAWN_TILE;
	uint8_t finishOpcode = FINISH_TILE;

	for (uint i = 0; i < _rows; i++){
		for (uint j = 0; j < _cols; j++){
			PathTile* t = _pathTiles[i][j];
			if (t != nullptr){
				player.SendByte(mapOpcode);
				player.SendByte(pathOpcode);
				player.SendInt32(t->GetXPos());
				player.SendInt32(t->GetYPos());
			}

			SolidGroundTile* st = _groundTiles[i][j];
			if (st != nullptr){
				player.SendByte(mapOpcode);
				player.SendByte(strucOpcode);
				player.SendInt32(st->GetXPos());
				player.SendInt32(st->GetYPos());
			}
		}
	}


	for (auto it = _spawnTiles.begin(); it != _spawnTiles.end(); ++it){
		player.SendByte(mapOpcode);
		player.SendByte(spawnOpcode);
		player.SendInt32((*it)->GetXPos());
		player.SendInt32((*it)->GetYPos());
	}

	for (auto it = _endTiles.begin(); it != _endTiles.end(); ++it){
		player.SendByte(mapOpcode);
		player.SendByte(finishOpcode);
		player.SendInt32((*it)->GetXPos());
		player.SendInt32((*it)->GetYPos());
	}

	uint8_t doneOpcode = MAP_FINISHED_LOADING;
	player.SendByte(doneOpcode);

}