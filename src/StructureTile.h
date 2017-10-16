#ifndef _STRUCTURE_TILE_
#define _STRUCTURE_TILE_

#include "Tile.h"

class StructureTile : public Tile {
public:
	StructureTile(unsigned int xPos, unsigned int yPos);
	~StructureTile();
	char GetSymbol();
};

#endif
