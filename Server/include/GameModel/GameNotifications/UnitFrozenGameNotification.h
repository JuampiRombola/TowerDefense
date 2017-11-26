#ifndef __UNIT_FROZEN_GAME_NOTIFICATION__
#define __UNIT_FROZEN_GAME_NOTIFICATION__

#include "GameNotification.h"
#include "../ViewModels/UnitVM.h"

class UnitFrozenGameNotification : public GameNotification
{
private:
	uint _unitId;
	uint _freeze_time_ms;
public:
	UnitFrozenGameNotification(uint unitId, uint freeze_time_ms);
	~UnitFrozenGameNotification();
	void Notify(std::vector<PlayerProxy*> playersToNotify);
};

#endif
