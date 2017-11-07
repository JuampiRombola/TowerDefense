#include <iostream>
#include "../../Protocolo.h"
#include "Notifications/NewLobbyNotification.h"

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

		uint8_t opcode = LOBBY_OPCODE; //Para el lobby
		p->sock.Send((char*) &opcode, 1);
		uint8_t instruction = CREATE_LOBBY; ///New lobby
		p->sock.Send((char*) &instruction, 1);
		int32_t guid = _lobby.GUID();
		p->sock.Send((char*) &guid, 4);

		std::string lobbyName = _lobby.Name();
		uint8_t lobbyNameSizeBuf = lobbyName.length();

		p->sock.Send((char*) &lobbyNameSizeBuf, 1);
		p->sock.Send(lobbyName.c_str(), lobbyName.length());
		std::cout << "new lobby noti sent to player " << p->GUID() << " \n" << std::flush;


	}
}