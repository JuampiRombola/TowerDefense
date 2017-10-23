#include <iostream>
#include <algorithm>
#include <memory>

#include "Map.h"
#include "Exceptions/UnitIsNotOnThisTileException.h"
#include "Exceptions/UnitIsAlreadyOnThisTileException.h"
#include "Exceptions/IncompletePathException.h"

#include "EnviormentUnit.h"
#include "PathTile.h"

PathTile::PathTile(uint xPos, uint yPos) 
: Tile(xPos, yPos), _canSpawn(false), _units() {}

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


void PathTile::UnitEnter(std::shared_ptr<EnviormentUnit> unit){
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.emplace_back(unit);
	else 
		throw new UnitIsAlreadyOnThisTileException();
}


void PathTile::UnitLeave(std::shared_ptr<EnviormentUnit> unit){

	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it != _units.end()){
		_units.erase(it);
	}
	else
		throw new UnitIsNotOnThisTileException();
}

bool PathTile::HasAnyUnit(){
	return _units.begin() != _units.end();
}

std::vector<std::shared_ptr<EnviormentUnit>> PathTile::GetUnits(){
	return _units;
}

bool PathTile::DrivesStraightToSpawnFrom(std::shared_ptr<PathTile> tile, Map* map){

	uint fromX = tile.get()->GetXPos();
	uint fromY = tile.get()->GetYPos();
	uint x = this->GetXPos();
	uint y = this->GetYPos();

	std::shared_ptr<PathTile> front;
	std::shared_ptr<PathTile> side1;
	std::shared_ptr<PathTile> side2;

	std::vector<std::shared_ptr<PathTile>> paths;

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

		if (front.get() != nullptr)
			paths.push_back(front);

		if (side1.get() != nullptr)
			paths.push_back(side1);

		if (side2.get() != nullptr)
			paths.push_back(side2);

		if (paths.size() > 1){
			return false;
		} else if (paths.size() == 0){
			throw new IncompletePathException();
		} else if (paths.size() == 1){
			if ((*paths.begin()).get()->CanSpawn()){
				return true;
			}

			if ((*paths.begin()) == map->GetFinishTile()){
				return false;
			}


			std::shared_ptr<PathTile> p = *paths.begin();
			fromX = x;
			fromY = y;
			x = p.get()->GetXPos();
			y = p.get()->GetYPos();
		}
	}

	return false;

}