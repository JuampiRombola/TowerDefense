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
    HordeUpdateGameNotification(uint hordeId, bool started);
    ~HordeUpdateGameNotification();
    void Notify(std::vector<PlayerProxy *> playersToNotify);
};


#endif //TOWERDEFENSE_HORDESTARTEDGAMENOTIFICATION_H
