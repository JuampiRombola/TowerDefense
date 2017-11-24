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
	unsigned long long _lastFireTimeStamp_ms;
	unsigned long long _lastVentiscaTimeStamp_ms;
	unsigned long long _lastTornadoTimeStamp_ms;
	uint _lastCrackDuration_ms;
	uint _lastFireDuration_ms;
	uint _lastVentiscaDuration_ms;
	uint _lastFireDamage;
	uint _lastVentiscaDamage;
	uint _lastVentiscaSlowPercent;
	uint _lastVentiscaSlowDuration_ms;
	uint _lastTornadoDuration_ms;
	uint _lastTornadoMaxDamage;
	bool _isCracked;
	bool _isOnFire;
	bool _hasVentisca;
	bool _hasTornado;
	bool _canSpawn;
	std::vector<EnviormentUnit*> _units;
	std::map<PathTile*, std::vector<PathTile*>> _possibleNextPaths;
	Map* _map;

	std::vector<std::tuple<unsigned long long, uint>> _damagesToApplyAfterDelay;

public:
	PathTile(uint xPos, uint yPos, Map* map, PathTile* next);
	~PathTile();
	PathTile* next;
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
	void Crack(uint time_ms);
	void SetOnFire(uint time_ms, uint fireDamage);
	Map* GetMap();
	void Ventisca(uint ventiscaDamage, uint ventiscaDuration_sec, uint slowDuration_sec, uint percentSlow);
	void Tornado(uint tornadoMaxDamage, uint tornadoDuration_sec);
	void HitUnitsAfterDelay(uint delay_ms, uint damage);
	void Step();
};

#endif
