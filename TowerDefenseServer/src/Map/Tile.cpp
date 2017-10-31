#include <algorithm>
#include <iostream>
#include <iterator>

#include "../../include/Map/Tile.h"

Tile::Tile(uint xPos, uint yPos) : _xPos(xPos), _yPos(yPos) 
{
}

Tile::~Tile(){}

uint Tile::GetXPos(){
	return _xPos;
}
uint Tile::GetYPos(){
	return _yPos;
}