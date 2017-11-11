#ifndef _SOLID_GROUND_TILE
#define _SOLID_GROUND_TILE

#include "Tile.h"

class Tower;
class Projectile;

class SolidGroundTile : public Tile {

private:
	Tower* _tower;

public:
	SolidGroundTile(uint xPos, uint yPos);
	~SolidGroundTile();
	char GetSymbol();
	void PlaceTower(Tower* tower);
	Tower* GetTower();
	bool HasTower();
	Projectile* Step();
};

#endif
