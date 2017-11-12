

#include <gtk/gtk.h>
#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../GTKRunner.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification
(Lobby& lobby)
: _lobby(lobby)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(GTKRunner& runner){
	gtk_widget_hide (GTK_WIDGET(runner.window_lobbies));
	gtk_widget_show (GTK_WIDGET(runner.window_lobby));

    GtkTreeIter    iter;
    /*GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
	gtk_label_set_text(runner.label_lobbyname, _lobbyName.c_str());
	std::cout << "JOINED THE LOBBY NAMED: '" << _lobbyName << "' !!" << '\n';
	for (auto it = _playerNames.begin(); it != _playerNames.end(); ++it){
		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set (GTK_LIST_STORE(model), &iter,
							COLUMN_PLAYER_NAME, (*it).c_str(),
							COLUMN_PLAYER_READY, false,
							-1);*/
	}
}