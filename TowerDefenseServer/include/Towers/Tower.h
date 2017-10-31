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

	Projectile*  _Fire(EnviormentUnit* target); 
	bool _CanFire(); 
	EnviormentUnit* _GetTargetUnitInRange();

	virtual Projectile* _BuildProjectile(PathTile* target) = 0;
public:
	Tower(uint cooldown_ms, uint range, uint damage, SolidGroundTile* position, Map* map);
	virtual ~Tower();
	Projectile* Step(); 
	virtual void PrintDebug() = 0;
	virtual bool Upgrade(const YAML::Node& cfg, UpgradeType type) = 0;
	void AddExperience(double exp);
	void AddDamage(uint damage);
	SolidGroundTile* GetPosition();

	virtual TowerVM GetViewModel() = 0;

};

#endif
