//
// Created by tino on 13/11/17.
//

#ifndef TOWERDEFENSE_UNITCREATEDGAMENOTIFICATION_H
#define TOWERDEFENSE_UNITCREATEDGAMENOTIFICATION_H

#include "GameNotification.h"
#include "../ViewModels/UnitVM.h"

class UnitCreatedGameNotification : public GameNotification
{
public:
    UnitCreatedGameNotification(UnitVM& viewmodel);
    ~UnitCreatedGameNotification();
    void Notify(std::vector<PlayerProxy*> playersToNotify);
    UnitVM vm;
};



#endif //TOWERDEFENSE_UNITCREATEDGAMENOTIFICATION_H
