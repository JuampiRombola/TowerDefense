#ifndef _MAP_
#define _MAP_

#include <vector>
#include <string>

#include "ITile.h"
#include "PathTile.h"
#include "SceneTile.h"
#include "StructureTile.h"
#include "IEnviormentUnit.h"

class Map{
private:
	uint _sideLength;
	std::vector<std::vector<ITile*>*> _tiles;
	PathTile* _spawnTile;
public:
	Map(uint sideLength, std::string mapJsonConfig);
	~Map();
	void DebugPrint();
	void SpawnUnit(IEnviormentUnit* unit);
};

#endif
