#ifndef _TOWER_
#define _TOWER_

#include <memory>

class Projectile;
class SolidGroundTile;
class Map;
class PathTile;
class EnviormentUnit;

class Tower {
protected:
	unsigned long long _lastTimeStamp_ms;
	uint _cooldown_ms;
	Map* _map;
	std::shared_ptr<SolidGroundTile> _position;
	uint _range;
	uint _experience;
	uint _damage;

	std::shared_ptr<Projectile>  _Fire(std::shared_ptr<EnviormentUnit> target); 
	bool _CanFire(); 
	std::shared_ptr<EnviormentUnit> _GetTargetUnitInRange();

	virtual std::shared_ptr<Projectile> _BuildProjectile(std::shared_ptr<PathTile> target) = 0;
public:
	Tower(uint cooldown_ms, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map);
	virtual ~Tower();
	std::shared_ptr<Projectile> Step(); 
	virtual void PrintDebug() = 0;
	void AddExperience(uint exp);
	void AddDamage(uint damage);
	std::shared_ptr<SolidGroundTile> GetPosition();

};

#endif
