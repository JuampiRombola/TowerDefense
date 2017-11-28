#include <iostream>
#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/NewLobbyNotification.h"
#include "../../../Client/include/Lobbies/Lobby.h"

NewLobbyNotification::NewLobbyNotification(Lobby& lobby) : 
_lobby(lobby) {
	
}

NewLobbyNotification::~NewLobbyNotification(){
	
}

void NewLobbyNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		if ((*it)->state == BROWSING_LOBBIES || (*it)->state == IN_LOBBY){
			_playersToNotify.push_back(*it);
		}
	}
}

void NewLobbyNotification::Notify(){
	
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		p->SendByte(CREATE_LOBBY);
		p->SendInt32(_lobby.GUID());
		std::string lobbyName = _lobby.Name();
		p->SendString(lobbyName);
		if (_lobby.MapCfg != nullptr)
			p->SendInt32(_lobby.MapCfg->Id());
		else
			p->SendInt32(-1);
	}
}