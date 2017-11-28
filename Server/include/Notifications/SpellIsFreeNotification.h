#ifndef __SPELL_IS_FREE_NOTIFICATION__
#define __SPELL_IS_FREE_NOTIFICATION__


#include "../Lobbies/Lobby.h"
#include "../../../Common/Protocolo.h"

class SpellIsFreeNotification : public Notification
{

private:
	SPELL_TYPE _spelltype;

public:
	SpellIsFreeNotification( SPELL_TYPE spelltype, std::vector<PlayerProxy*>& tonotify);
	~SpellIsFreeNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
};

#endif