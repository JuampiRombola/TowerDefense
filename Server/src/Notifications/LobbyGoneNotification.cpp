
#include "../../include/Notifications/LobbyGoneNotification.h"
#include "../../../Common/Protocolo.h"

LobbyGoneNotification::LobbyGoneNotification(Lobby& lobby) : _lobby(lobby) {

}

LobbyGoneNotification::~LobbyGoneNotification(){
	
}

void LobbyGoneNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->state == BROWSING_LOBBIES || (*it)->state == IN_LOBBY){
			_playersToNotify.push_back(*it);
		}
	}
}

void LobbyGoneNotification::Notify(){
	
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		p->SendByte(LOBBY_GONE);
		p->SendInt32(_lobby.GUID());
	}
}