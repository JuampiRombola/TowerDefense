#ifndef _MAP_
#define _MAP_

#include <vector>
#include <string>


#include "Tile.h"
#include "PathTile.h"
#include "SolidGroundTile.h"
#include "EnviormentUnit.h"

class Map{
private:
	//Synchronization
	uint _rows;
	uint _cols;

	PathTile* _finishTile;

	std::vector<Tile*> _tiles;

	std::vector<PathTile*> _spawnTiles;
	std::vector<std::vector<PathTile*>> _pathTiles;
	std::vector<std::vector<SolidGroundTile*>> _groundTiles;

	void _PlaceTile(Tile* tile);
	void _PlaceGroundTile(SolidGroundTile* tile);
	void _PlacePathTile(PathTile* tile);
	void _SetSpawnTile(PathTile* tile);
public:
	Map(uint rows, uint cols, std::string mapJsonConfig);
	~Map();
	
	void PlaceUnit(EnviormentUnit* unit, PathTile* tile);

	PathTile* GetPathTile(uint x, uint y);
	PathTile* GetRandomSpawnTile();
	SolidGroundTile* GetSolidGroundTile(uint x, uint y);

	std::vector<EnviormentUnit*> GetUnitsInRadius(uint range, Tile* tile);

	PathTile* GetFinishTile();
};

#endif
