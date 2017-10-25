#include <iostream>
#include <algorithm>
#include <memory>
#include <map>

#include "Map/Map.h"
#include "Exceptions/UnitIsNotOnThisTileException.h"
#include "Exceptions/UnitIsAlreadyOnThisTileException.h"
#include "Exceptions/IncompletePathException.h"

#include "EnviormentUnits/EnviormentUnit.h"
#include "Helpers.h"
#include "Map/PathTile.h"

PathTile::PathTile(uint xPos, uint yPos) 
: Tile(xPos, yPos), _lastCrackTimeStamp_ms(0), _lastCrackDuration_ms(0), _isCracked(false),
 _canSpawn(false), _units(), _possibleNextPaths() {}


PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}

void PathTile::Crack(uint seconds){
	_isCracked = true;
	_lastCrackTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastCrackDuration_ms = seconds * 1000;
	std::vector<std::shared_ptr<EnviormentUnit>> v = _units;
	for (auto it = v.begin(); it != v.end(); ++it){
		(*it).get()->Kill();
	}
}

void PathTile::InitPossiblePaths(Map* map){
	std::shared_ptr<PathTile> up = map->GetPathTile(GetXPos(), GetYPos() + 1);
	std::shared_ptr<PathTile> down = map->GetPathTile(GetXPos(), GetYPos() - 1);
	std::shared_ptr<PathTile> left = map->GetPathTile(GetXPos() - 1, GetYPos());
	std::shared_ptr<PathTile> right = map->GetPathTile(GetXPos() + 1, GetYPos());
	if (up != std::shared_ptr<PathTile>(nullptr)){
		try
		{
			if (!up.get()->DrivesStraightToSpawnFrom(this, map)){

				if (down != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[down.get()].push_back(std::weak_ptr<PathTile>(up));

				if (left != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[left.get()].push_back(std::weak_ptr<PathTile>(up));

				if (right != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[right.get()].push_back(std::weak_ptr<PathTile>(up));
			}
		} catch (...) { /* */ }

	}

	if (down != std::shared_ptr<PathTile>(nullptr)){
		try
		{
			if (!down.get()->DrivesStraightToSpawnFrom(this, map)){

				if (up != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[up.get()].push_back(std::weak_ptr<PathTile>(down));

				if (left != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[left.get()].push_back(std::weak_ptr<PathTile>(down));

				if (right != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[right.get()].push_back(std::weak_ptr<PathTile>(down));
			}
		} catch (...) { /* */ }
	}

	if (right != std::shared_ptr<PathTile>(nullptr)){
		try
		{
			if (!right.get()->DrivesStraightToSpawnFrom(this, map)){

				if (up != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[up.get()].push_back(std::weak_ptr<PathTile>(right));

				if (left != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[left.get()].push_back(std::weak_ptr<PathTile>(right));

				if (down != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[down.get()].push_back(std::weak_ptr<PathTile>(right));
			}
		} catch (...) { /* */ }
	}

	if (left != std::shared_ptr<PathTile>(nullptr)){
		try
		{
			if (!left.get()->DrivesStraightToSpawnFrom(this, map)){

				if (up != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[up.get()].push_back(std::weak_ptr<PathTile>(left));

				if (right != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[right.get()].push_back(std::weak_ptr<PathTile>(left));

				if (down != std::shared_ptr<PathTile>(nullptr))
					_possibleNextPaths[down.get()].push_back(std::weak_ptr<PathTile>(left));
			}
		} catch (...) { /* */ }
	}
}


bool PathTile::CanSpawn(){
	return _canSpawn;
}

void PathTile::SetCanSpawn(){
	_canSpawn = true;
}


void PathTile::UnitEnter(std::shared_ptr<EnviormentUnit> unit){
	if (_isCracked){
		unsigned long long ts_ms = Helpers::MillisecondsTimeStamp();
		uint delta_ms = ts_ms - _lastCrackTimeStamp_ms;
		if (delta_ms > _lastCrackDuration_ms){
			_isCracked = false;
			_lastCrackDuration_ms = 0;
		} else {
			unit.get()->Kill();
			return;
		}
	}

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

std::vector<std::weak_ptr<PathTile>> PathTile::GetPossibleNextTiles(PathTile* from){
	if (from == NULL)
		return std::vector<std::weak_ptr<PathTile>>();
	return _possibleNextPaths[from];
}

bool PathTile::DrivesStraightToSpawnFrom(PathTile* tile, Map* map){

	uint fromX = tile->GetXPos();
	uint fromY = tile->GetYPos();
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