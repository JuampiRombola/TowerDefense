//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_HORDESTARTEDGAMENOTIFICATION_H
#define TOWERDEFENSE_HORDESTARTEDGAMENOTIFICATION_H


#include <zconf.h>
#include "GameNotification.h"

class HordeUpdateGameNotification : public GameNotification {
private:
    uint _hordeId;
    bool _started;
public:
    HordeUpdateGameNotification(uint hordeId, std::vector<PlayerProxy*> playerToNotify, bool started);
    ~HordeUpdateGameNotification();
    void Notify();
};


#endif //TOWERDEFENSE_HORDESTARTEDGAMENOTIFICATION_H
