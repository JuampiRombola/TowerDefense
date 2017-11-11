#ifndef __UNIT_POS_GAME_NOTIFICATION__
#define __UNIT_POS_GAME_NOTIFICATION__

#include "GameNotification.h"
#include "../ViewModels/UnitVM.h"

class UnitPositionGameNotification : public GameNotification
{
public:
	UnitPositionGameNotification(UnitVM& vm);
	~UnitPositionGameNotification();
	void Notify();
	UnitVM vm;
};

#endif
