//
// Created by tino on 20/11/17.
//

#ifndef TOWERDEFENSE_MAPTRANSFERNOTIFICATION_H
#define TOWERDEFENSE_MAPTRANSFERNOTIFICATION_H

#include "../../PlayerProxy.h"
#include "../Map/Map.h"
#include "GameNotification.h"

class MapTransferNotification : public GameNotification {
private:
    Map& _map;
    PlayerProxy& _player;
public:
    MapTransferNotification(Map& map, PlayerProxy& player);
    ~MapTransferNotification();
    void Notify(std::vector<PlayerProxy*> playersToNotify);
};


#endif //TOWERDEFENSE_MAPTRANSFERNOTIFICATION_H