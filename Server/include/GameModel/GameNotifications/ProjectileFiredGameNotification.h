//
// Created by tino on 13/11/17.
//

#ifndef TOWERDEFENSE_PROJECTILEFIREDGAMENOTIFICATION_H
#define TOWERDEFENSE_PROJECTILEFIREDGAMENOTIFICATION_H


#include "GameNotification.h"
#include "../ViewModels/ProjectileVM.h"

class ProjectileFiredGameNotification : public GameNotification
{
private:
    ProjectileVM vm;
public:
    ProjectileFiredGameNotification(ProjectileVM vm, std::vector<PlayerProxy*> playersToNotify);
    ~ProjectileFiredGameNotification();
    void Notify();
};



#endif //TOWERDEFENSE_PROJECTILEFIREDGAMENOTIFICATION_H
