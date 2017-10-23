#ifndef _SOLID_GROUND_TILE
#define _SOLID_GROUND_TILE

#include <memory>

#include "Tile.h"

class Tower;
class Projectile;

class SolidGroundTile : public Tile {

private:
	std::shared_ptr<Tower> _tower;

public:
	SolidGroundTile(unsigned int xPos, unsigned int yPos);
	~SolidGroundTile();
	char GetSymbol();
	void PlaceTower(std::shared_ptr<Tower> tower);
	bool HasTower();
	std::shared_ptr<Projectile> Step();
};

#endif
