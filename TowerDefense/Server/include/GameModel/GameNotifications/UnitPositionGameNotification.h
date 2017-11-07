#ifndef __UNIT_POS_GAME_NOTIFICATION__
#define __UNIT_POS_GAME_NOTIFICATION__

#include "GameModel/ViewModels/UnitVM.h"
#include "GameModel/GameNotifications/GameNotification.h"

class UnitPositionGameNotification : public GameNotification
{
public:
	UnitPositionGameNotification(UnitVM& vm);
	~UnitPositionGameNotification();
	void Notify();
	UnitVM vm;
};

#endif
