#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/InvalidLogInNotification.h"


InvalidLogInNotification::InvalidLogInNotification(PlayerProxy& player) : _player(player) {
	
}

InvalidLogInNotification::~InvalidLogInNotification(){
	
}

void InvalidLogInNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void InvalidLogInNotification::Notify(){
	uint8_t opcode = LOG_IN_FAILED;
	_player.sock.Send((char*) &opcode, 1);
}