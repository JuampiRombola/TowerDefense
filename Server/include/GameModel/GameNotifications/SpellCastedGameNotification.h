#ifndef __SPELL_CASTED_GAME_NOTIFICATION__
#define __SPELL_CASTED_GAME_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../GameNotifications/GameNotification.h"
#include "../../../../Common/Protocolo.h"

class SpellCastedGameNotification : public GameNotification
{
private:
	uint32_t _cooldown_ms;
	CAST_SPELL_TYPE _type;
	uint32_t _x;
	uint32_t _y;
	uint32_t _duration_ms;
public:
	SpellCastedGameNotification(CAST_SPELL_TYPE type, uint32_t x, uint32_t y, uint32_t duration_ms, uint32_t cooldown_ms);
	~SpellCastedGameNotification();
	void Notify(std::vector<PlayerProxy*> playersToNotify);
	
};

#endif