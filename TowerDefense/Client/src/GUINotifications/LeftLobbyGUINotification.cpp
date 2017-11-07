#include "GUINotifications/LeftLobbyGUINotification.h"


LeftLobbyGUINotification::LeftLobbyGUINotification(std::vector<Lobby*>& lobbies) : _lobbies(lobbies) {
	
}

LeftLobbyGUINotification::~LeftLobbyGUINotification(){
	
}

void LeftLobbyGUINotification::Execute(){
	std::cout << "LEFT LOBBY, NOW BROWSING LOBBIES\n " << std::flush;
	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		Lobby* l = *it;		
		std::cout << "Lobby: '" << l->Name() << "', guid: " << l->GUID() << "\n " << std::flush;
	}
}