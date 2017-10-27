#ifndef _MAP_
#define _MAP_

#include <vector>
#include <string>


class Tile;
class Projectile;
class PathTile;
class EnviormentUnit;

#include "Map/SolidGroundTile.h"

class Map{
private:
	uint _rows;
	uint _cols;

	PathTile* _finishTile;

	std::vector<Tile*> _tiles;

	std::vector<PathTile*> _spawnTiles;
	std::vector<std::vector<PathTile*>> _pathTiles;
	std::vector<std::vector<SolidGroundTile*>> _groundTiles;

	std::vector<Projectile*> _projectiles;

	void _PlaceTile(Tile* tile);
	void _PlacePathTile(PathTile* tile);
	void _SetSpawnTile(PathTile* tile);
public:
	Map(uint rows, uint cols, std::string mapJsonConfig);
	~Map();
	
	void RemoveUnit(EnviormentUnit* unit);
	void PlaceUnit(EnviormentUnit* unit, PathTile* tile);

	PathTile* GetPathTile(uint x, uint y);
	PathTile* GetRandomSpawnTile();
	SolidGroundTile* GetSolidGroundTile(uint x, uint y);

	std::vector<EnviormentUnit*> GetUnitsInRadius(uint range, Tile* tile);

	PathTile* GetFinishTile();
	std::vector<PathTile*> GetTilesInRange(PathTile* tile, uint range);

	void PlaceGroundTile(SolidGroundTile* tile);

	void Step();
};

#endif
