//
// Created by tino on 12/11/17.
//

#ifndef TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H
#define TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"


class PlayerJoinedLobbyGTKNotification : public GTKNotification {
private:

    OtherPlayer& _player;
public:
    PlayerJoinedLobbyGTKNotification(OtherPlayer& player);
    ~PlayerJoinedLobbyGTKNotification();
    void Execute(GTKRunner& runner);
};


#endif //TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H
