//
// Created by tino on 27/11/17.
//

#include "../../include/GTKNotifications/PlayerIsReadyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

PlayerIsReadyGTKNotification::PlayerIsReadyGTKNotification(uint pguid) 
: _pguid(pguid) 
{
    
}

PlayerIsReadyGTKNotification::~PlayerIsReadyGTKNotification() {
    
}

void PlayerIsReadyGTKNotification::Execute(GTKmmRunner &runner) {
    runner.fixed_lobby.SetPlayerReadyStatus(_pguid, true);    
}