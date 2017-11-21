//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_HORDEMANAGER_H
#define TOWERDEFENSE_HORDEMANAGER_H

#include <queue>
#include "Horde.h"
#include "../Helpers.h"
#include "../GameConfiguration.h"
#include "../GameNotifications/GameNotification.h"
#include "../../ThreadSafeQueue.h"
class TowerDefenseGame;

class HordeManager {
private:
    std::queue<Horde*> _hordes;
    unsigned long long _timeStamp;
    Horde* _currentHorde;
public:
    HordeManager(GameConfiguration& mapCfg);
    ~HordeManager();
    void AddHorde(Horde* horde);
    void Step();
    uint timeToWaitBetweenHordes_ms;
    TowerDefenseGame* game;
};


#endif //TOWERDEFENSE_HORDEMANAGER_H
