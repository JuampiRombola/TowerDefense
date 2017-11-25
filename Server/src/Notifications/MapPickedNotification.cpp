//
// Created by tino on 22/11/17.
//

#include "../../include/Notifications/MapPickedNotification.h"
#include "../../../Common/Protocolo.h"


MapPickedNotification::MapPickedNotification(uint mapid, uint lobbyid) : _mapid(mapid), _lobbyId(lobbyid) {}

MapPickedNotification::~MapPickedNotification() {}

void MapPickedNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
        PlayerProxy* p = *it;
        if (p->state != IN_GAME){
            uint8_t opcode = PICK_MAP;
            p->SendByte(opcode);
            p->SendInt32(_mapid);
            p->SendInt32(_lobbyId);
        }
    }
}

void MapPickedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
    _playersToNotify = *players;
}
