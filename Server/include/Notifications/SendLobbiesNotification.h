#ifndef __SEND_LOBBIES_NOTIFICATION__
#define __SEND_LOBBIES_NOTIFICATION__

#include "../Notifications/Notification.h"
#include "../PlayerProxy.h"
#include <tuple>
#include <vector>
#include <string>
#include "../../../Common/Protocolo.h"
#include "../Lobbies/Lobby.h"

class SendLobbiesNotification : public Notification {
private:
	PlayerProxy& _player;
	std::vector<Lobby*> _toNotify;
public:
	SendLobbiesNotification(PlayerProxy& player);
	~SendLobbiesNotification();
	void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
	void Notify();
	void AddLobby(Lobby* lobby);
};

#endif