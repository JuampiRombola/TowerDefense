#include <iostream>
#include <cmath>

#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Helpers.h"

Projectile::Projectile(Tower* origin, PathTile* target, uint projectile_ms_over_tile, uint hitpoints) :
 _ms_over_tile(projectile_ms_over_tile), _impacted(false), _distance(0),
 _lastTimeStamp_ms(0), _origin(origin), _hitPoints(hitpoints), _target(target)
{
	uint dx = abs(origin->GetPosition()->GetXPos() - target->GetXPos());
	uint dy = abs(origin->GetPosition()->GetYPos() - target->GetYPos());
	uint temp = (dx*dx) + (dy*dy);
	double sq = sqrt(temp);
	_distance = floor(sq);
	if (_distance < 1)
		_distance = 1;
}

Projectile::~Projectile(){}


void Projectile::Step(){
	if (_impacted)
		return;

	unsigned long long actualTs_ms = Helpers::MillisecondsTimeStamp();
	if (_lastTimeStamp_ms == 0)
		_lastTimeStamp_ms = actualTs_ms;

	if (actualTs_ms - _lastTimeStamp_ms > (_ms_over_tile * _distance)){
		double exp = _OnImpact();
		_origin->AddExperience(exp);
		_impacted = true;
	}
}

void Projectile::PrintDebug(){
	
}

bool Projectile::Impacted(){
	return _impacted;
}