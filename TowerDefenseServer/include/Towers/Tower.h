#ifndef _TOWER_
#define _TOWER_

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
	SolidGroundTile* _position;
	uint _range;
	uint _experience;
	uint _damage;

	Projectile*  _Fire(EnviormentUnit* target); 
	bool _CanFire(); 
	EnviormentUnit* _GetTargetUnitInRange();

	virtual Projectile* _BuildProjectile(PathTile* target) = 0;
public:
	Tower(uint cooldown_ms, uint range, uint damage, SolidGroundTile* position, Map* map);
	virtual ~Tower();
	Projectile* Step(); 
	virtual void PrintDebug() = 0;
	void AddExperience(uint exp);
	void AddDamage(uint damage);
	SolidGroundTile* GetPosition();

};

#endif
