#ifndef _MAP_
#define _MAP_

#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>

struct temp_pathTile {
	uint x;
	uint y;
	uint xsig;
	uint ysig;
};


class Tile;
class Projectile;
class PathTile;
class EnviormentUnit;

#include "../Map/SolidGroundTile.h"
#include "../Configuration.h"
#include "../../PlayerProxy.h"

class TowerDefenseGame;

class Map{
private:
	uint _rows;
	uint _cols;

	std::vector<Tile*> _tiles;

	std::vector<PathTile*> _spawnTiles;
	std::vector<PathTile*> _endTiles;
	std::vector<std::vector<PathTile*>> _pathTiles;
	std::vector<std::vector<SolidGroundTile*>> _groundTiles;

	std::vector<Projectile*> _projectiles;

	void _PlaceTile(Tile* tile);
	void _PlacePathTile(PathTile* tile);
	void _SetSpawnTile(PathTile* tile);
	void _SetFinishTile(PathTile* tile);
public:
	Map(uint rows, uint cols, Configuration& mapCfg);
	~Map();
	void RemoveUnit(EnviormentUnit* unit);
	void PlaceUnit(EnviormentUnit* unit, PathTile* tile);
	PathTile* GetPathTile(uint x, uint y);
	PathTile* GetRandomSpawnTile();
	SolidGroundTile* GetSolidGroundTile(uint x, uint y);
	std::vector<EnviormentUnit*> GetUnitsInRadius(uint range, Tile* tile);
	std::vector<PathTile*> GetFinishTiles();
	std::vector<PathTile*> GetPathTilesInRange(Tile* tile, uint range);
	void PlaceGroundTile(SolidGroundTile* tile);
	void Step(TowerDefenseGame& game);
	std::vector<Projectile*> GetProjectiles();
	std::vector<Tower*> GetTowers();
	void TransferMapTo(PlayerProxy& player);
	bool AreCoordinatesInsideMap(uint x, uint y);
};

#endif
