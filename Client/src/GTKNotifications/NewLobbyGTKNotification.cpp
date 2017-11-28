

#include "../../include/GTKNotifications/NewLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


NewLobbyGTKNotification::NewLobbyGTKNotification(Lobby& lobby) : _lobby(lobby) {
	
}

NewLobbyGTKNotification::~NewLobbyGTKNotification(){
	
}

void NewLobbyGTKNotification::Execute(GTKmmRunner& runner){

    runner.fixed_lobbies.NewLobby(_lobby.Name(), _lobby.GUID());

}
