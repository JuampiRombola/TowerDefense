

#include "GUINotifications/NewLobbyGUINotification.h"


NewLobbyGUINotification::NewLobbyGUINotification(Lobby& lobby) : _lobby(lobby) {
	
}

NewLobbyGUINotification::~NewLobbyGUINotification(){
	
}

void NewLobbyGUINotification::Execute(){
	std::cout << "NEW LOBBY: '" << _lobby.Name() << "', guid: " << _lobby.GUID() << '\n';
}