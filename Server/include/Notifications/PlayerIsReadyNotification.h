//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_PLAYERISREADYNOTIFICATION_H
#define TOWERDEFENSE_PLAYERISREADYNOTIFICATION_H


#include "../PlayerProxy.h"
#include "Notification.h"
#include "../Lobbies/Lobby.h"

class PlayerIsReadyNotification : public Notification {
private:
    Lobby& _lobby;
    PlayerProxy& _player;
public:
    PlayerIsReadyNotification(Lobby& lobby, PlayerProxy& player);
    ~PlayerIsReadyNotification();
    void Notify();
    void SetPlayersToNotify(std::vector<PlayerProxy*>* players);

};


#endif //TOWERDEFENSE_PLAYERISREADYNOTIFICATION_H
