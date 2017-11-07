#include "Notifications/LoggedInNotification.h"
#include "../../Protocolo.h"
#include <iostream>

LoggedInNotification::LoggedInNotification(PlayerProxy& player) : _player(player) {
	
}

LoggedInNotification::~LoggedInNotification(){
	
}

void LoggedInNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void LoggedInNotification::Notify(){
	uint8_t opcode = LOG_IN_SUCCESS;
	_player.sock.Send((char*) &opcode, 1);
}