//
// Created by tino on 23/11/17.
//

#ifndef TOWERDEFENSE_LOBBYPICKEDMAPGTKNOTIFICATION_H
#define TOWERDEFENSE_LOBBYPICKEDMAPGTKNOTIFICATION_H


#include "GTKNotification.h"

class LobbyPickedMapGTKNotification : public GTKNotification {
private:
    uint _lobbyId;
    uint _mapId;
public:
    LobbyPickedMapGTKNotification(uint lobbyId, uint mapId);
    ~LobbyPickedMapGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_LOBBYPICKEDMAPGTKNOTIFICATION_H
