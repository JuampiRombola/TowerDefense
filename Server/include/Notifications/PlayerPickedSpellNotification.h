#ifndef __PLAYER_PICKED_SPELL_NOTIFICATION__
#define __PLAYER_PICKED_SPELL_NOTIFICATION__

#include <stdint.h>
#include <vector>

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../../Common/Protocolo.h"

class PlayerPickedSpellNotification : public Notification
{

private:
	PlayerProxy& _player;
	SPELL_TYPE _spelltype;
	Lobby& _lobby;
	bool _notifyThePlayer;
public:
	PlayerPickedSpellNotification(PlayerProxy& player, Lobby &lobby, SPELL_TYPE spelltype, bool notifyThePlayer);
	~PlayerPickedSpellNotification();

	void Notify();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	
};

#endif