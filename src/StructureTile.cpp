#include <iostream>
#include "StructureTile.h"

StructureTile::StructureTile(unsigned int xPos, unsigned int yPos) : Tile(xPos, yPos) {}

StructureTile::~StructureTile(){}

char StructureTile::GetSymbol(){
	return 'L';
}