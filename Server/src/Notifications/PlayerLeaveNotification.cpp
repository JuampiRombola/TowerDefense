#include <iostream>
#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/PlayerLeaveNotification.h"

PlayerLeaveNotification::PlayerLeaveNotification(uint32_t guid) :
        _playerGUID(guid) {

}

PlayerLeaveNotification::~PlayerLeaveNotification(){

}

void PlayerLeaveNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
    for (auto it = players->begin(); it != players->end(); ++it){
        if ((*it)->GUID() != _playerGUID){
            _playersToNotify.push_back(*it);
        }
    }
}

void PlayerLeaveNotification::Notify(){

    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
        PlayerProxy* p = *it;

        uint8_t opcode = PLAYER_LEAVE;
        p->sock.Send((char*) &opcode, 1);

        p->sock.Send((char*) &_playerGUID, 4);

    }
}