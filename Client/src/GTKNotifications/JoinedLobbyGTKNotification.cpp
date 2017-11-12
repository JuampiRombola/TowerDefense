

#include <gtk/gtk.h>
#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../GTKRunner.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification
(std::string lobbyName, std::vector<std::string>& playerNames)
: _lobbyName(lobbyName), _playerNames(playerNames)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(GTKRunner& runner){
	gtk_widget_hide (GTK_WIDGET(runner.window_lobbies));
	gtk_widget_show (GTK_WIDGET(runner.window_lobby));

	std::cout << "JOINED THE LOBBY NAMED: '" << _lobbyName << "' !!" << '\n';
	for (auto it = _playerNames.begin(); it != _playerNames.end(); ++it){
		std::cout << *it << " is in the lobby\n";
	}
}