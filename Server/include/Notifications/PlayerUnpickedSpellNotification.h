#ifndef __PLAYER_UNPICKED_SPELL_NOTIFICATION__
#define __PLAYER_UNPICKED_SPELL_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../../Common/Protocolo.h"

class PlayerUnpickedSpellNotification : public Notification
{

private:
	PlayerProxy& _player;
	SPELL_TYPE _spelltype;
	Lobby& _lobby;
public:
	PlayerUnpickedSpellNotification(PlayerProxy& player, Lobby &lobby, SPELL_TYPE spelltype);
	~PlayerUnpickedSpellNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif