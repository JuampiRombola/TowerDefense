//
// Created by tino on 19/11/17.
//

#ifndef TOWERDEFENSE_GAMEMODELSTARTEDRUNNINGNOTIFICATION_H
#define TOWERDEFENSE_GAMEMODELSTARTEDRUNNINGNOTIFICATION_H


#include "GameNotification.h"

class GameModelStartedRunningNotification : public GameNotification {
public:
    GameModelStartedRunningNotification();
    ~GameModelStartedRunningNotification();
    void Notify(std::vector<PlayerProxy *> playersToNotify);
};


#endif //TOWERDEFENSE_GAMEMODELSTARTEDRUNNINGNOTIFICATION_H