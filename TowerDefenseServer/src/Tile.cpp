#include <algorithm>
#include <iostream>
#include <iterator>

#include "Tile.h"

Tile::Tile(uint xPos, uint yPos) : _xPos(xPos), _yPos(yPos) 
{
	//std::cout << "Tile init: " << xPos << ", " << yPos << '\n';
}

Tile::~Tile(){}

uint Tile::GetXPos(){
	return _xPos;
}
uint Tile::GetYPos(){
	return _yPos;
}