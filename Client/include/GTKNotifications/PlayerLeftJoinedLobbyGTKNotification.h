//
// Created by tino on 12/11/17.
//

#ifndef TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H
#define TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"


class PlayerLeftJoinedLobbyGTKNotification : public GTKNotification {
private:
    OtherPlayer& _player;
    Lobby& _lobby;
    bool _inmylobby;
    bool _joined;
public:
    PlayerLeftJoinedLobbyGTKNotification(OtherPlayer& player, Lobby& lobby, bool inmylobby, bool joined);
    ~PlayerLeftJoinedLobbyGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_PLAYERJOINEDLOBBYGTKNOTIFICATION_H
