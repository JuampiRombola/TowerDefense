

#include "GUINotifications/UpdateLobbyPlayersGUINotification.h"


UpdateLobbyPlayersGUINotification::UpdateLobbyPlayersGUINotification
(std::vector<std::string>& playerNames)
: _playerNames(playerNames)
{
}

UpdateLobbyPlayersGUINotification::~UpdateLobbyPlayersGUINotification(){
	
}

void UpdateLobbyPlayersGUINotification::Execute(){
	std::cout << "LOBBY UPDATE!!" << '\n';
	for (auto it = _playerNames.begin(); it != _playerNames.end(); ++it){
		std::cout << *it << " is in the lobby\n";
	}
}