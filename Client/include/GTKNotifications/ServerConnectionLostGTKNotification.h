//
// Created by tino on 28/11/17.
//

#ifndef TOWERDEFENSE_SERVERCONNECTIONLOSTGTKNOTIFICATION_H
#define TOWERDEFENSE_SERVERCONNECTIONLOSTGTKNOTIFICATION_H


#include "GTKNotification.h"

class ServerConnectionLostGTKNotification : public GTKNotification {

public:
    ServerConnectionLostGTKNotification();
    ~ServerConnectionLostGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_SERVERCONNECTIONLOSTGTKNOTIFICATION_H
