#include "../../include/Notifications/GameStartedNotification.h"
#include "../../../Common/Protocolo.h"
#include "../../include/Lobbies/Lobby.h"
#include <iostream>

GameStartedNotification::GameStartedNotification(Lobby& lobby, uint8_t sup, uint width, uint height)
: _lobby(lobby), _sup(sup), _width(width), _height(height)
{

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
		p->SendByte(ins);
		p->SendByte(_sup);
		p->SendInt32(_width);
		p->SendInt32(_height);
	}
}