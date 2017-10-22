#ifndef _SOLID_GROUND_TILE
#define _SOLID_GROUND_TILE

#include "Tile.h"

class Tower;

class SolidGroundTile : public Tile {

private:
	Tower* _tower;

public:
	SolidGroundTile(unsigned int xPos, unsigned int yPos);
	~SolidGroundTile();
	char GetSymbol();
	void PlaceTower(Tower* tower);
	bool HasTower();
};

#endif
