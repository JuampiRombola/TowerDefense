#include "../../include/GTKNotifications/LobbyIsGoneGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

LobbyIsGoneGTKNotification::LobbyIsGoneGTKNotification(uint32_t lobbyGuid) : _lobbyGuid(lobbyGuid) {
	
}

LobbyIsGoneGTKNotification::~LobbyIsGoneGTKNotification(){
	
}

void LobbyIsGoneGTKNotification::Execute(GTKmmRunner& runner){

    runner.fixed_lobbies.RemoveLobby(_lobbyGuid);
}