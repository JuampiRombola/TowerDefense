

#include "../../include/GTKNotifications/NewLobbyGTKNotification.h"


NewLobbyGTKNotification::NewLobbyGTKNotification(Lobby& lobby) : _lobby(lobby) {
	
}

NewLobbyGTKNotification::~NewLobbyGTKNotification(){
	
}

//void NewLobbyGTKNotification::Execute(){
//	std::cout << "NEW LOBBY: '" << _lobby.Name() << "', guid: " << _lobby.GUID() << '\n';
//}

void NewLobbyGTKNotification::Execute(GTKRunner& runner){
    std::cout << "NEW LOBBY: '" << _lobby.Name() << "', guid: " << _lobby.GUID() << '\n';
}
