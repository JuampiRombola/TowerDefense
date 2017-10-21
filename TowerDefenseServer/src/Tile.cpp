#include <algorithm>
#include <iterator>

#include "Tile.h"

Tile::Tile(unsigned int xPos, unsigned int yPos) : _xPos(xPos), _yPos(yPos) 
{

}

Tile::~Tile(){}

unsigned int Tile::GetXPos(){
	return _xPos;
}
unsigned int Tile::GetYPos(){
	return _yPos;
}