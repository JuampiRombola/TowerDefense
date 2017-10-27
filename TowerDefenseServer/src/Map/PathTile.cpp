#include <iostream>
#include <algorithm>

#include <map>

#include "Map/Map.h"
#include "Exceptions/UnitIsNotOnThisTileException.h"
#include "Exceptions/UnitIsAlreadyOnThisTileException.h"
#include "Exceptions/IncompletePathException.h"

#include "EnviormentUnits/EnviormentUnit.h"
#include "Helpers.h"
#include "Map/PathTile.h"

PathTile::PathTile(uint xPos, uint yPos, Map* map) 
: Tile(xPos, yPos), _lastCrackTimeStamp_ms(0), _lastCrackDuration_ms(0), _isCracked(false),
 _canSpawn(false), _units(), _possibleNextPaths(), _map(map) {}


PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}

void PathTile::Crack(uint seconds){
	_isCracked = true;
	_lastCrackTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastCrackDuration_ms = seconds * 1000;
	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Kill();
	}
}

Map* PathTile::GetMap(){
	return _map;
}

void PathTile::InitPossiblePaths(){
	PathTile* up = _map->GetPathTile(GetXPos(), GetYPos() + 1);
	PathTile* down = _map->GetPathTile(GetXPos(), GetYPos() - 1);
	PathTile* left = _map->GetPathTile(GetXPos() - 1, GetYPos());
	PathTile* right = _map->GetPathTile(GetXPos() + 1, GetYPos());
	if (up != NULL){
		try
		{
			if (!up->DrivesStraightToSpawnFrom(this)){

				if (down != NULL)
					_possibleNextPaths[down].push_back(up);

				if (left != NULL)
					_possibleNextPaths[left].push_back(up);

				if (right != NULL)
					_possibleNextPaths[right].push_back(up);
			}
		} catch (...) { /* */ }

	}

	if (down != NULL){
		try
		{
			if (!down->DrivesStraightToSpawnFrom(this)){

				if (up != NULL)
					_possibleNextPaths[up].push_back(down);

				if (left != NULL)
					_possibleNextPaths[left].push_back(down);

				if (right != NULL)
					_possibleNextPaths[right].push_back(down);
			}
		} catch (...) { /* */ }
	}

	if (right != NULL){
		try
		{
			if (!right->DrivesStraightToSpawnFrom(this)){

				if (up != NULL)
					_possibleNextPaths[up].push_back(right);

				if (left != NULL)
					_possibleNextPaths[left].push_back(right);

				if (down != NULL)
					_possibleNextPaths[down].push_back(right);
			}
		} catch (...) { /* */ }
	}

	if (left != NULL){
		try
		{
			if (!left->DrivesStraightToSpawnFrom(this)){

				if (up != NULL)
					_possibleNextPaths[up].push_back(left);

				if (right != NULL)
					_possibleNextPaths[right].push_back(left);

				if (down != NULL)
					_possibleNextPaths[down].push_back(left);
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


void PathTile::UnitEnter(EnviormentUnit* unit){
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.emplace_back(unit);
	else 
		throw new UnitIsAlreadyOnThisTileException();

	if (_isCracked){
		unsigned long long ts_ms = Helpers::MillisecondsTimeStamp();
		uint delta_ms = ts_ms - _lastCrackTimeStamp_ms;
		if (delta_ms > _lastCrackDuration_ms){
			_isCracked = false;
			_lastCrackDuration_ms = 0;
		} else {
			std::cout << "FALLED INTO CRACK\n" << std::flush;
			unit->Kill();
		}
	}
}


void PathTile::UnitLeave(EnviormentUnit* unit){

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

std::vector<EnviormentUnit*> PathTile::GetUnits(){ //copia!!!!!
	return _units;
}

std::vector<PathTile*> PathTile::GetPossibleNextTiles(PathTile* from){
	if (from == NULL)
		return std::vector<PathTile*>();
	return _possibleNextPaths[from];
}

bool PathTile::DrivesStraightToSpawnFrom(PathTile* tile){

	uint fromX = tile->GetXPos();
	uint fromY = tile->GetYPos();
	uint x = this->GetXPos();
	uint y = this->GetYPos();

	PathTile* front;
	PathTile* side1;
	PathTile* side2;

	std::vector<PathTile*> paths;

	while (true){
		paths.clear();
		if (fromX == x){
			uint dif = fromY - y;
			front = _map->GetPathTile(x, y - dif);
			side1 = _map->GetPathTile(x + 1, y);
			side2 = _map->GetPathTile(x - 1, y);
		} else if (fromY == y){
			uint dif = fromX - x;
			front = _map->GetPathTile(x - dif, y);
			side1 = _map->GetPathTile(x, y + 1);
			side2 = _map->GetPathTile(x, y - 1);	
		} 

		if (front != nullptr)
			paths.push_back(front);

		if (side1 != nullptr)
			paths.push_back(side1);

		if (side2 != nullptr)
			paths.push_back(side2);

		if (paths.size() > 1){
			return false;
		} else if (paths.size() == 0){
			throw new IncompletePathException();
		} else if (paths.size() == 1){
			if ((*paths.begin())->CanSpawn()){
				return true;
			}

			if ((*paths.begin()) == _map->GetFinishTile()){
				return false;
			}


			PathTile* p = *(paths.begin());
			fromX = x;
			fromY = y;
			x = p->GetXPos();
			y = p->GetYPos();
		}
	}

	return false;

}