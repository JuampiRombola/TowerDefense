#ifndef _ICE_TOWER_
#define _ICE_TOWER_

#include <memory>

#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class IceTower : public Tower {
protected:
	std::shared_ptr<Projectile> _BuildProjectile(std::shared_ptr<PathTile> target);
public:
	IceTower(uint cooldown_sec, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map);
	~IceTower();
	void PrintDebug();
};

#endif
