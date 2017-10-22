#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <vector>
#include <mutex>

#include "Tile.h"

class Map;
class EnviormentUnit;
class PathTile;

class PathTile : public Tile {
private:
	std::mutex _unitsMutex;

	bool _canSpawn;
	std::vector<EnviormentUnit*> _units;
public:
	PathTile(uint xPos, uint yPos);
	~PathTile();
	char GetSymbol();
	bool CanSpawn();
	void SetCanSpawn();

	bool HasAnyUnit();

	std::vector<EnviormentUnit*> GetUnits();

	bool DrivesStraightToSpawnFrom(PathTile* tile, Map* map);

	void UnitLeave(EnviormentUnit* unit);
	void UnitEnter(EnviormentUnit* unit);
};

#endif
