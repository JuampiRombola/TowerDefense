#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Map.h"
#include "PathTile.h"
#include "EnviormentUnit.h"
#include "Exceptions/NonPlacedUnitCannotStepException.h"
#include "Exceptions/IncompletePathException.h"
#include "Exceptions/UnitCannotMoveDiagonallyException.h"

EnviormentUnit::EnviormentUnit(uint id, uint speed): 
_id(id), _speed(speed), _movementTimer(0),
_position(NULL), _lastPosition(NULL), _map(NULL) {


}

EnviormentUnit::~EnviormentUnit(){

}

void EnviormentUnit::Step(){
	if (_position == NULL || _map == NULL)
		throw new NonPlacedUnitCannotStepException();

	_movementTimer ++;
	if (_movementTimer != _speed)
		return;

	_movementTimer = 0;

	
	int x = _position->GetXPos();
	int y = _position->GetYPos();

	std::vector<PathTile*> possiblePaths;

	if (_lastPosition == NULL){

		PathTile* up = _map->GetPathTile(x, y+1);
		PathTile* down = _map->GetPathTile(x, y-1);
		PathTile* right = _map->GetPathTile(x+1, y);
		PathTile* left = _map->GetPathTile(x-1, y);
		std::vector<PathTile*> paths;
		if (up != NULL)		possiblePaths.push_back(up);
		if (down != NULL) 	possiblePaths.push_back(down);
		if (right != NULL) 	possiblePaths.push_back(right);
		if (left != NULL) 	possiblePaths.push_back(left);

	} else {
		int lastX = _lastPosition->GetXPos();
		int lastY = _lastPosition->GetYPos();

		PathTile* front = NULL;
		PathTile* side1 = NULL;
		PathTile* side2 = NULL;

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

		if (front != NULL){
			if (front == _map->GetFinishTile() || !front->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(front);
		}

		if (side1 != NULL){
			if (side1 == _map->GetFinishTile() || !side1->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(side1);
		}

		if (side2 != NULL){
			if (side2 == _map->GetFinishTile() || !side2->DrivesStraightToSpawnFrom(_position, _map))
				possiblePaths.push_back(side2);
		}
	}

	if (possiblePaths.size() == 0)
		throw new IncompletePathException();

	std::srand(std::time(0));
	uint random_variable = (uint) std::rand() % possiblePaths.size();
	PathTile* next = possiblePaths[random_variable];

	_position->UnitLeave(this);
	_lastPosition = _position;
	next->UnitEnter(this);
	_position = next;

	this->PrintDebug();
}

PathTile* EnviormentUnit::GetPosition(){
	return _position;
}

void EnviormentUnit::SetPosition(PathTile* pos, Map* map){
	_position = pos;
	_map = map;
}
unsigned int EnviormentUnit::GetId(){
	return _id;
}

