//
// Created by tino on 12/11/17.
//

#ifndef TOWERDEFENSE_PLAYERLEFTLOBBYGTKNOTIFICATION_H
#define TOWERDEFENSE_PLAYERLEFTLOBBYGTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"

class PlayerLeftLobbyGTKNotification : public GTKNotification {
private:

    OtherPlayer& _player;
public:
    PlayerLeftLobbyGTKNotification(OtherPlayer& player);
    ~PlayerLeftLobbyGTKNotification();
    void Execute(GTKRunner& runner);
};


#endif //TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H
