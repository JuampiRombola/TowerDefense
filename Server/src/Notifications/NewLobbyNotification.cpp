#include <iostream>
#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/NewLobbyNotification.h"

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
		uint8_t instruction = CREATE_LOBBY; ///New lobby
		p->SendByte(instruction);
		int32_t guid = _lobby.GUID();
		p->SendInt32(guid);
		std::string lobbyName = _lobby.Name();
		p->SendString(lobbyName);
	}
}