#include <iostream>
#include <mutex>
#include <algorithm>

#include "Map.h"
#include "UnitIsNotOnThisTileException.h"
#include "UnitIsAlreadyOnThisTileException.h"
#include "EnviormentUnit.h"
#include "IncompletePathException.h"
#include "PathTile.h"

PathTile::PathTile(uint xPos, uint yPos) 
: Tile(xPos, yPos), _unitsMutex(), _canSpawn(false), _units() {}

PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}


bool PathTile::CanSpawn(){
	return _canSpawn;
}

void PathTile::SetCanSpawn(){
	_canSpawn = true;
}


void PathTile::UnitEnter(EnviormentUnit* unit){
	std::lock_guard<std::mutex> lock(_unitsMutex);
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.emplace_back(unit);
	else 
		throw new UnitIsAlreadyOnThisTileException();
}


void PathTile::UnitLeave(EnviormentUnit* unit){
	std::lock_guard<std::mutex> lock(_unitsMutex);
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it != _units.end())
		_units.erase(it);
	else
		throw new UnitIsNotOnThisTileException();
}

bool PathTile::HasAnyUnit(){
	std::lock_guard<std::mutex> lock(_unitsMutex);
	return _units.begin() != _units.end();
}

std::vector<EnviormentUnit*> PathTile::GetUnits(){
	std::lock_guard<std::mutex> lock(_unitsMutex);
	std::vector<EnviormentUnit*> v;
	for (auto it = _units.begin(); it != _units.end(); ++it)
		v.push_back(*it);

	return v;
}

bool PathTile::DrivesStraightToSpawnFrom(PathTile* tile, Map* map){

	uint fromX = tile->GetXPos();
	uint fromY = tile->GetYPos();
	uint x = this->GetXPos();
	uint y = this->GetYPos();

	PathTile* front = NULL;
	PathTile* side1 = NULL;
	PathTile* side2 = NULL;

	std::vector<PathTile*> paths;

	while (true){
		paths.clear();
		if (fromX == x){
			uint dif = fromY - y;
			front = map->GetPathTile(x, y - dif);
			side1 = map->GetPathTile(x + 1, y);
			side2 = map->GetPathTile(x - 1, y);
		} else if (fromY == y){
			uint dif = fromX - x;
			front = map->GetPathTile(x - dif, y);
			side1 = map->GetPathTile(x, y + 1);
			side2 = map->GetPathTile(x, y - 1);	
		} 

		if (front != NULL)
			paths.push_back(front);

		if (side1 != NULL)
			paths.push_back(side1);

		if (side2 != NULL)
			paths.push_back(side2);

		if (paths.size() > 1){
			return false;
		} else if (paths.size() == 0){
			throw new IncompletePathException();
		} else if (paths.size() == 1){
			if ((*paths.begin())->CanSpawn()){
				return true;
			}

			if ((*paths.begin()) == map->GetFinishTile()){
				return false;
			}


			PathTile* p = *paths.begin();
			fromX = x;
			fromY = y;
			x = p->GetXPos();
			y = p->GetYPos();
		}
	}

	return false;

}