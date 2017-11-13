//
// Created by tino on 12/11/17.
//

#ifndef TOWERDEFENSE_PLAYERLEAVENOTIFICATION_H
#define TOWERDEFENSE_PLAYERLEAVENOTIFICATION_H


#include "Notification.h"

class PlayerLeaveNotification : public Notification
{

private:
    uint32_t _playerGUID;
public:
    PlayerLeaveNotification(uint32_t guid);
    ~PlayerLeaveNotification();

    void Notify();
    void SetPlayersToNotify(std::vector<PlayerProxy*>* players);

};

#endif //TOWERDEFENSE_PLAYERLEAVENOTIFICATION_H
