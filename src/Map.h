#ifndef _MAP_
#define _MAP_

#include <vector>
#include <map>
#include <string>

#include "Tile.h"
#include "PathTile.h"
#include "StructureTile.h"
#include "EnviormentUnit.h"

class Map{
private:
	uint _sideLength;

	PathTile* _spawnTile;
	PathTile* _finishTile;

	std::vector<PathTile*> _pathTiles;
	std::vector<StructureTile*> _structureTiles;

public:
	Map(uint sideLength, std::string mapJsonConfig);
	~Map();
	void SpawnUnit(EnviormentUnit* unit);
	PathTile* GetSpawnTile();
	PathTile* GetFinishTile();
};

#endif
