#ifndef _MAP_
#define _MAP_

#include <vector>
#include <map>
#include <string>
#include <mutex>


#include "Tile.h"
#include "PathTile.h"
#include "SolidGroundTile.h"
#include "EnviormentUnit.h"

class Map{
private:
	//Synchronization
	std::mutex _spawnTilesMutex;

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

	// "Pone la unit en la tile "

	void PlaceUnit(EnviormentUnit* unit, PathTile* tile);

	PathTile* GetPathTile(uint x, uint y);
	PathTile* GetRandomSpawnTile();


	PathTile* GetFinishTile();
};

#endif
