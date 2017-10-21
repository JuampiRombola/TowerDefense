#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <vector>

#include "Tile.h"


class EnviormentUnit;
class PathTile;

class PathTile : public Tile {
private:
	PathTile* _next;
	bool _canSpawn;
	std::vector<EnviormentUnit*> _units;
public:
	PathTile(uint xPos, uint yPos);
	~PathTile();
	char GetSymbol();
	PathTile* Next();
	void SetNextTile(PathTile* tile);
	bool CanSpawn();
	void SetCanSpawn();
	void Place(EnviormentUnit* unit);

	bool HasAnyUnit();

	void UnitLeave(EnviormentUnit* unit);
	void UnitEnter(EnviormentUnit* unit);
};

#endif
