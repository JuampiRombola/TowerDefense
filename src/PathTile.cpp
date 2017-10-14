#include <iostream>
#include "PathTile.h"

PathTile::PathTile(Direction dir) : _direction(dir), _units() {}

PathTile::~PathTile(){}

bool PathTile::AcceptsStructures(){
	return false;
}

bool PathTile::IsPath(){
	return true;
}

Direction PathTile::GetDirection(){
	return _direction;
}

char PathTile::GetSymbol(){
	switch (_direction){
		case up:
			return 'u';
		case down:
			return 'd';
		case right:
			return 'r';
		case left: 
			return 'l';
		default:
			return 'P';
	}
}