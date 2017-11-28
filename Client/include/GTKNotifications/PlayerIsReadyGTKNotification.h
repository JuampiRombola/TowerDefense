//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_PLAYERISREADYGTKNOTIFICATION_H
#define TOWERDEFENSE_PLAYERISREADYGTKNOTIFICATION_H


#include <zconf.h>
#include "GTKNotification.h"

class PlayerIsReadyGTKNotification : public GTKNotification {
private:
    uint _pguid;
public:
    PlayerIsReadyGTKNotification(uint pguid);
    ~PlayerIsReadyGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_PLAYERISREADYGTKNOTIFICATION_H
