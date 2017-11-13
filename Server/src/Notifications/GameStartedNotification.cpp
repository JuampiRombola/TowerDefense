#include "../../include/Notifications/GameStartedNotification.h"
#include "../../../Common/Protocolo.h"
#include "../../include/Lobbies/Lobby.h"
#include <iostream>

GameStartedNotification::GameStartedNotification(Lobby& lobby)
: _lobby(lobby){

}

GameStartedNotification::~GameStartedNotification(){

}

void GameStartedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void GameStartedNotification::Notify(){
	std::vector<PlayerProxy*> playersInLobby = _lobby.GetPlayersInLobbyWithSomeSpellSet();
	for (auto it = playersInLobby.begin(); it != playersInLobby.end(); ++it){
		PlayerProxy* p = *it;
		uint8_t ins = GAME_STARTED;
		p->sock.Send((char*) &ins, 1);
	}
}