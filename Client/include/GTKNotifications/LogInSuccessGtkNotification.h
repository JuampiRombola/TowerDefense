//
// Created by tino on 11/11/17.
//

#ifndef TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H
#define TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H

#include "GTKNotification.h"

class LogInSuccessGtkNotification : public GTKNotification{
public:
    LogInSuccessGtkNotification();
    ~LogInSuccessGtkNotification();
    void Execute(GTKRunner& runner);
};


#endif //TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H
