#ifndef __UNIT_POS_GAME_NOTIFICATION__
#define __UNIT_POS_GAME_NOTIFICATION__

#include "../ViewModels/UnitVM.h"
#include "../GameNotifications/GameNotification.h"

class UnitPositionGameNotification : public GameNotification
{
public:
	UnitPositionGameNotification(UnitVM& vm);
	~UnitPositionGameNotification();
	void NotifyUnits(std::vector<UnitView*>& units, TextureLoader &textures,
					 Renderer &renderer);
	void NotifyShots(std::vector<ShotView*>& shots, TextureLoader& textures,
				 Renderer &renderer);
	UnitVM vm;
};

#endif
