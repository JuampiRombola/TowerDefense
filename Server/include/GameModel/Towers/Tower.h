#ifndef _TOWER_
#define _TOWER_

class Projectile;
class SolidGroundTile;
class Map;
class PathTile;
class EnviormentUnit;
class TowerVM;
#include "../Commands/UpgradeTowerCommand.h"
#include "yaml-cpp/yaml.h"
#include "../Commands/BuildTowerCommand.h"
#include <mutex>
class Tower {
protected:
	unsigned long long _lastTimeStamp_ms;
	uint _cooldown_ms;
	Map* _map;
	SolidGroundTile* _position;
	uint _range;
	double _experience;
	uint _damage;
	uint _upgradeLevel;
	uint _projectile_ms_over_tile;

	Projectile*  _Fire(EnviormentUnit* target); 
	bool _CanFire(); 
	EnviormentUnit* _GetTargetUnitInRange(TowerType type);
	ThreadSafeQueue<GameNotification*>& _notifications;
	virtual Projectile* _BuildProjectile(PathTile* target) = 0;
public:
	Tower(uint cooldown_ms, uint range, uint damage,
		  SolidGroundTile* position, Map* map, uint projectile_ms_over_tile,
	 ThreadSafeQueue<GameNotification*>& notifications);
	virtual ~Tower();
	Projectile* Step(); 
	virtual void PrintDebug() = 0;
	virtual bool Upgrade(UpgradeType type) = 0;
	void AddExperience(double exp);
	SolidGroundTile* GetPosition();

	virtual TowerVM GetViewModel() = 0;
	virtual TowerType GetTowerType() = 0;

	const YAML::Node* cfg;
};

#endif
