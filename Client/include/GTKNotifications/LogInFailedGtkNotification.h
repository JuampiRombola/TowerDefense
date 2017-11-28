//
// Created by tino on 11/11/17.
//

#ifndef TOWERDEFENSE_LogInFailedGTKNOTIFICATION_H
#define TOWERDEFENSE_LogInFailedGTKNOTIFICATION_H

#include "GTKNotification.h"

class LogInFailedGtkNotification : public GTKNotification{
public:
    LogInFailedGtkNotification();
    ~LogInFailedGtkNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_LogInFailedGTKNOTIFICATION_H
