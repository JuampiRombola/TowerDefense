#ifndef _MAP_
#define _MAP_

#include <vector>
#include <map>
#include <string>

#include "Tile.h"
#include "PathTile.h"
#include "SolidGroundTile.h"
#include "EnviormentUnit.h"

class Map{
private:
	uint _sideLength;

	std::vector<PathTile*> _spawnTiles;
	PathTile* _finishTile;

	std::vector<PathTile*> _pathTiles;
	std::vector<SolidGroundTile*> _groundTiles;

	// Setea "tile" como SpawnTile, si la tile 
	// ya es spawn no hace nada.
	void _SetSpawnTile(PathTile* tile);

public:
	Map(uint sideLength, std::string mapJsonConfig);
	~Map();

	// "Pone la unit en la tile "

	void SpawnUnit(EnviormentUnit* unit, PathTile* tile);

	std::vector<PathTile*>& SpawnTiles();


	PathTile* GetFinishTile();
};

#endif
