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
	std::vector<PlayerProxy*> players = _lobby.GetPlayers();

	PlayerProxy* fire = _lobby.GetFirePlayer();
	PlayerProxy* ground = _lobby.GetGroundPlayer();
	PlayerProxy* air = _lobby.GetAirPlayer();
	PlayerProxy* water = _lobby.GetWaterPlayer();


	for (auto it = players.begin(); it != players.end(); ++it){
		PlayerProxy* p = *it;
		uint8_t ins = GAME_STARTED;
		p->SendByte(ins);
		p->SendByte(_sup);
		p->SendInt32(_width);
		p->SendInt32(_height);
		if (p == fire)
			p->SendByte(1);
		else
			p->SendByte(0);

		if (p == water)
			p->SendByte(1);
		else
			p->SendByte(0);

		if (p == air)
			p->SendByte(1);
		else
			p->SendByte(0);

		if (p == ground)
			p->SendByte(1);
		else
			p->SendByte(0);

	}
}