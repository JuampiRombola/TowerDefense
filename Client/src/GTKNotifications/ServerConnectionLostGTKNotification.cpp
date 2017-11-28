//
// Created by tino on 28/11/17.
//

#include "../../include/GTKNotifications/ServerConnectionLostGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

ServerConnectionLostGTKNotification::ServerConnectionLostGTKNotification(){
    
}
ServerConnectionLostGTKNotification::~ServerConnectionLostGTKNotification(){
    
}
void ServerConnectionLostGTKNotification::Execute(GTKmmRunner& runner){
    runner.ConnectionLost();
}