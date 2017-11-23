//
// Created by tino on 22/11/17.
//

#ifndef TOWERDEFENSE_MAPPICKEDNOTIFICATION_H
#define TOWERDEFENSE_MAPPICKEDNOTIFICATION_H

#include "Notification.h"

class MapPickedNotification : public Notification {
private:
    uint32_t _mapid;
    uint32_t _lobbyId;
public:
    MapPickedNotification(uint mapid, uint lobbyId);
    ~MapPickedNotification();
    void Notify();
    void SetPlayersToNotify(std::vector<PlayerProxy*>* players);
};


#endif //TOWERDEFENSE_MAPPICKEDNOTIFICATION_H
