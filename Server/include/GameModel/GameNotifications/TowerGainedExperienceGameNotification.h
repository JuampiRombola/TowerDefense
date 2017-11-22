//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_TOWERGAINEDEXPERIENCEGAMENOTIFICATION_H
#define TOWERDEFENSE_TOWERGAINEDEXPERIENCEGAMENOTIFICATION_H


#include "GameNotification.h"

class TowerGainedExperienceGameNotification : public GameNotification {
private:
    uint _x;
    uint _y;
    uint _exp;
public:
    TowerGainedExperienceGameNotification(uint x, uint y, uint exp);
    ~TowerGainedExperienceGameNotification();
    void Notify(std::vector<PlayerProxy*> playersToNotify);
};


#endif //TOWERDEFENSE_TOWERGAINEDEXPERIENCEGAMENOTIFICATION_H
