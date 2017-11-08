#ifndef __GAME_NOTIFICATION__
#define __GAME_NOTIFICATION__

#include <vector>
#include "../../../View/Model/UnitView.h"
#include "../../../View/Model/TowerView.h"
#include "../../../View/Model/ShotView.h"

class GameNotification 
{
public:
	GameNotification();
	virtual ~GameNotification();
	virtual void NotifyUnits(std::vector<UnitView*>& units, TextureLoader
	&textures, Renderer &renderer) = 0;
	virtual void NotifyShots(std::vector<ShotView*>& shots, TextureLoader
	&textures, Renderer &renderer) = 0;

};

#endif
