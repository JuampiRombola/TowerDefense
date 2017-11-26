#ifndef __UNIT_SPEED_UPDATE_GAME_NOTIFICATION__
#define __UNIT_SPEED_UPDATE_GAME_NOTIFICATION__

#include "GameNotification.h"
#include "../ViewModels/UnitVM.h"

class UnitSpeedUpdateGameNotification : public GameNotification
{
private:
	uint _unitId;
	uint _stepDelay_ms;
public:
	UnitSpeedUpdateGameNotification(uint unitId, uint stepDelay_ms);
	~UnitSpeedUpdateGameNotification();
	void Notify(std::vector<PlayerProxy*> playersToNotify);
};

#endif
