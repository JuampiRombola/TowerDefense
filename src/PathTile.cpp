#include <iostream>
#include "PathTile.h"
#include "EnviormentUnit.h"

PathTile::PathTile(unsigned int xPos, unsigned int yPos) 
: Tile(xPos, yPos), _next(NULL) {}

PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}

PathTile* PathTile::Next(){
	return _next;
}

void PathTile::SetNextTile(PathTile* tile){
	_next = tile;
}