#ifndef _MAP_
#define _MAP_

#include <vector>
#include <string>
#include <memory>

class Tile;
class Projectile;
class PathTile;
class EnviormentUnit;

#include "Map/SolidGroundTile.h"

class Map{
private:
	//Synchronization
	uint _rows;
	uint _cols;

	std::shared_ptr<PathTile> _finishTile;

	std::vector<std::shared_ptr<Tile>> _tiles;

	std::vector<std::shared_ptr<PathTile>> _spawnTiles;
	std::vector<std::vector<std::shared_ptr<PathTile>>> _pathTiles;
	std::vector<std::vector<std::shared_ptr<SolidGroundTile>>> _groundTiles;

	std::vector<std::shared_ptr<Projectile>> _projectiles;

	void _PlaceTile(std::shared_ptr<Tile> tile);
	void _PlaceGroundTile(std::shared_ptr<SolidGroundTile> tile);
	void _PlacePathTile(std::shared_ptr<PathTile> tile);
	void _SetSpawnTile(std::shared_ptr<PathTile> tile);
public:
	Map(uint rows, uint cols, std::string mapJsonConfig);
	~Map();
	
	void RemoveUnit(std::shared_ptr<EnviormentUnit> unit);
	void PlaceUnit(std::shared_ptr<EnviormentUnit> unit, std::shared_ptr<PathTile> tile);

	std::shared_ptr<PathTile> GetPathTile(uint x, uint y);
	std::shared_ptr<PathTile> GetRandomSpawnTile();
	std::shared_ptr<SolidGroundTile> GetSolidGroundTile(uint x, uint y);

	std::vector<std::shared_ptr<EnviormentUnit>> GetUnitsInRadius(uint range, std::shared_ptr<Tile> tile);

	std::shared_ptr<PathTile> GetFinishTile();

	void Step();
};

#endif
