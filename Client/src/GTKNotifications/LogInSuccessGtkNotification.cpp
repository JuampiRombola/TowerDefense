//
// Created by tino on 11/11/17.
//

#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../GTKRunner.h"

LogInSuccessGtkNotification::LogInSuccessGtkNotification(){

}

LogInSuccessGtkNotification::~LogInSuccessGtkNotification(){

}

void LogInSuccessGtkNotification::Execute(GTKRunner& runner){
    runner.LogInSuccess();
}