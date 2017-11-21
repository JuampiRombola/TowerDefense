#ifndef __UNIT_DIED_GAME_NOTIFICATION__
#define __UNIT_DIED_GAME_NOTIFICATION__

#include "GameNotification.h"
#include "../ViewModels/UnitVM.h"

class UnitDiedGameNotification : public GameNotification
{
public:
	UnitDiedGameNotification(UnitVM& vm );
	~UnitDiedGameNotification();
	void Notify(std::vector<PlayerProxy*> playersToNotify);
	UnitVM vm;
};

#endif
