#ifndef __SPELL_CASTED_GAME_NOTIFICATION__
#define __SPELL_CASTED_GAME_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"

class SpellCastedGameNotification : public Notification
{
public:
	SpellCastedGameNotification();
	~SpellCastedGameNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif