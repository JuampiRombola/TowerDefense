#ifndef _SOLID_GROUND_TILE
#define _SOLID_GROUND_TILE

#include "Tile.h"
#include "Tower.h"

class SolidGroundTile : public Tile {

private:
	Tower* _tower;

public:
	SolidGroundTile(unsigned int xPos, unsigned int yPos);
	~SolidGroundTile();
	char GetSymbol();

	void PlaceTower(Tower* tower);
};

#endif
