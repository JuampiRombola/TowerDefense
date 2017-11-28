#include "../../include/GTKNotifications/LeftLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


LeftLobbyGTKNotification::LeftLobbyGTKNotification() {
	
}

LeftLobbyGTKNotification::~LeftLobbyGTKNotification(){
	
}

void LeftLobbyGTKNotification::Execute(GTKmmRunner& runner){
    runner.box->remove(*runner.fixed_lobby.fixed);
    runner.box->add(*runner.fixed_lobbies.fixed);
}