//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_TOWERUPGRADEDGAMENOTIFICATION_H
#define TOWERDEFENSE_TOWERUPGRADEDGAMENOTIFICATION_H


#include "../ViewModels/TowerVM.h"

class TowerUpgradedGameNotification : public GameNotification {
private:
    TowerVM _vm;
public:
    TowerUpgradedGameNotification(TowerVM vm);
    ~TowerUpgradedGameNotification();
    void Notify(std::vector<PlayerProxy*> playersToNotify);
};


#endif //TOWERDEFENSE_TOWERUPGRADEDGAMENOTIFICATION_H
