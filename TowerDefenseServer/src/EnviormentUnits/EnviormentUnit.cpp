#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>

#include "Map/Map.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "Helpers.h"
#include "Exceptions/NonPlacedUnitCannotStepException.h"
#include "Exceptions/IncompletePathException.h"
#include "Exceptions/UnitCannotMoveDiagonallyException.h"

EnviormentUnit::EnviormentUnit(uint id, uint speed, uint healthpoints): 
_lastTimeStamp_ms(0), _alive(true), _id(id), _speed(speed),
 _healthPoints(healthpoints), _position(std::shared_ptr<PathTile>(nullptr)), 
_lastPosition(std::shared_ptr<PathTile>(nullptr)), 
_map(NULL) 
{

}

EnviormentUnit::~EnviormentUnit(){

}

void EnviormentUnit::GetHit(uint hitpoints){
	_healthPoints -= hitpoints;
	std::cout << "EnviormentUnit" << _id << " GOT HIT for " << hitpoints 
	<< "hp, now has " << _healthPoints << "hp\n" << std::flush;
	if (_healthPoints <= 0)
		_alive = false;
}

bool EnviormentUnit::IsAlive(){
	return _alive;
}

void EnviormentUnit::Step(std::shared_ptr<EnviormentUnit> thisUnit){

	if (!_CanStep())
		return;

	std::shared_ptr<PathTile> next = _GetNextTile();

	_position.get()->UnitLeave(thisUnit); 
	next.get()->UnitEnter(thisUnit);

	_lastPosition = _position;
	_position = next;

	PrintDebug();
}


bool EnviormentUnit::_CanStep(){
	if (_position.get() == nullptr || _map == NULL)
		throw new NonPlacedUnitCannotStepException();

	if (_lastTimeStamp_ms == 0){
		_lastTimeStamp_ms = Helpers::MillisecondsTimeStamp();
		return true;
	}

	if (Helpers::TimeElapsed(_lastTimeStamp_ms, _speed)){
		_lastTimeStamp_ms = Helpers::MillisecondsTimeStamp();
		return true;
	}

	return false;
}

std::shared_ptr<PathTile> EnviormentUnit::_GetNextTile(){
	int x = _position->GetXPos();
	int y = _position->GetYPos();

	std::vector<std::shared_ptr<PathTile>> possiblePaths;

	if (_lastPosition.get() == nullptr){

		std::shared_ptr<PathTile> up = _map->GetPathTile(x, y+1);
		std::shared_ptr<PathTile> down = _map->GetPathTile(x, y-1);
		std::shared_ptr<PathTile> right = _map->GetPathTile(x+1, y);
		std::shared_ptr<PathTile> left = _map->GetPathTile(x-1, y);
		std::vector<std::shared_ptr<PathTile>> paths;
		if (up.get() != nullptr)	possiblePaths.push_back(up);
		if (down.get() != nullptr) 	possiblePaths.push_back(down);
		if (right.get() != nullptr) possiblePaths.push_back(right);
		if (left.get() != nullptr) 	possiblePaths.push_back(left);

	} else {
		int lastX = _lastPosition->GetXPos();
		int lastY = _lastPosition->GetYPos();

		std::shared_ptr<PathTile> front(nullptr);
		std::shared_ptr<PathTile> side1(nullptr);
		std::shared_ptr<PathTile> side2(nullptr);

		if (lastX == x){
			uint dif = lastY - y;
			front = _map->GetPathTile(x, y - dif);
			side1 = _map->GetPathTile(x + 1, y);
			side2 = _map->GetPathTile(x - 1, y);	
		} else if (lastY == y){
			uint dif = lastX - x;
			front = _map->GetPathTile(x - dif, y);
			side1 = _map->GetPathTile(x, y + 1);
			side2 = _map->GetPathTile(x, y - 1);	
		} else {
			throw new UnitCannotMoveDiagonallyException();
		}

		if (front.get() != nullptr){
			if (front == _map->GetFinishTile() || !front->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(front);
		}

		if (side1.get() != nullptr){
			if (side1 == _map->GetFinishTile() || !side1->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(side1);
		}

		if (side2.get() != nullptr){
			if (side2 == _map->GetFinishTile() || !side2->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(side2);
		}
	}

	if (possiblePaths.size() == 0)
		throw new IncompletePathException();

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % possiblePaths.size();
	return possiblePaths[random_variable];
}

std::shared_ptr<PathTile> EnviormentUnit::GetPosition(){
	return _position;
}

void EnviormentUnit::SetPosition(std::shared_ptr<PathTile> pos, Map* map){
	_position = pos;
	_map = map;
}
unsigned int EnviormentUnit::GetId(){
	return _id;
}

