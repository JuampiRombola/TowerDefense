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
	unsigned long long _lastCrackTimeStamp_ms;
	uint _lastCrackDuration_ms;
	bool _isCracked;
	bool _canSpawn;
	std::vector<std::shared_ptr<EnviormentUnit>> _units;
	std::map<PathTile*, std::vector<std::weak_ptr<PathTile>>> _possibleNextPaths;

public:
	PathTile(uint xPos, uint yPos);
	~PathTile();
	char GetSymbol();
	bool CanSpawn();
	void SetCanSpawn();

	void InitPossiblePaths(Map* map);

	bool HasAnyUnit();

	std::vector<std::shared_ptr<EnviormentUnit>> GetUnits();

	bool DrivesStraightToSpawnFrom(PathTile* tile, Map* map);

	std::vector<std::weak_ptr<PathTile>> GetPossibleNextTiles(PathTile* from);
	
	void UnitLeave(std::shared_ptr<EnviormentUnit> unit);
	void UnitEnter(std::shared_ptr<EnviormentUnit> unit);

	void Crack(uint seconds);
};

#endif
