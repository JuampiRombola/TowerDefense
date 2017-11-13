#ifndef __TOWER_PLACED_GAME_NOTIFICATION__
#define __TOWER_PLACED_GAME_NOTIFICATION__

#include "GameNotification.h"
#include "../ViewModels/TowerVM.h"

class TowerPlacedGameNotification : public GameNotification
{
public:
	TowerPlacedGameNotification(TowerVM& vm, std::vector<PlayerProxy*> playersToNotify);
	~TowerPlacedGameNotification();
	void Notify();
	TowerVM vm;
};

#endif
