

#include "../../include/GUINotifications/JoinedLobbyGUINotification.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification
(std::string lobbyName, std::vector<std::string>& playerNames)
: _lobbyName(lobbyName), _playerNames(playerNames)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(){
	std::cout << "JOINED THE LOBBY NAMED: '" << _lobbyName << "' !!" << '\n';
	for (auto it = _playerNames.begin(); it != _playerNames.end(); ++it){
		std::cout << *it << " is in the lobby\n";
	}
}