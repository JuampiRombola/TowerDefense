//
// Created by tino on 11/11/17.
//

#include "../../include/GTKNotifications/LogInFailedGtkNotification.h"
#include "../../GTKRunner.h"


LogInFailedGtkNotification::LogInFailedGtkNotification(){

}

LogInFailedGtkNotification::~LogInFailedGtkNotification(){

}

void LogInFailedGtkNotification::Execute(GTKRunner& runner){
    runner.MessageBox("Log in failed! Name already taken");
}