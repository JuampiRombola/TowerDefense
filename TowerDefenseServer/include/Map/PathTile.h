#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <vector>
#include <map>
#include <memory>

#include "Tile.h"


class Map;
class EnviormentUnit;
class PathTile;

class PathTile : public Tile {
private:
	bool _canSpawn;
	std::vector<std::shared_ptr<EnviormentUnit>> _units;
public:
	PathTile(uint xPos, uint yPos);
	~PathTile();
	char GetSymbol();
	bool CanSpawn();
	void SetCanSpawn();

	bool HasAnyUnit();

	std::vector<std::shared_ptr<EnviormentUnit>> GetUnits();

	bool DrivesStraightToSpawnFrom(std::shared_ptr<PathTile> tile, Map* map);

	void UnitLeave(std::shared_ptr<EnviormentUnit> unit);
	void UnitEnter(std::shared_ptr<EnviormentUnit> unit);
};

#endif
