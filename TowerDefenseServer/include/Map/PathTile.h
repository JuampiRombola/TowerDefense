#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <vector>
#include <map>


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
	std::vector<EnviormentUnit*> _units;
	std::map<PathTile*, std::vector<PathTile*>> _possibleNextPaths;
	Map* _map;

public:
	PathTile(uint xPos, uint yPos, Map* map);
	~PathTile();
	char GetSymbol();
	bool CanSpawn();
	void SetCanSpawn();
	void InitPossiblePaths();
	bool HasAnyUnit();
	std::vector<EnviormentUnit*> GetUnits();
	bool DrivesStraightToSpawnFrom(PathTile* tile);
	std::vector<PathTile*> GetPossibleNextTiles(PathTile* from);
	void UnitLeave(EnviormentUnit* unit);
	void UnitEnter(EnviormentUnit* unit);
	void Crack(uint seconds);
	Map* GetMap();
};

#endif
