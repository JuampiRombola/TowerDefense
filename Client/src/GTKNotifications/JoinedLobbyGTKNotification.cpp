

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

	runner.CreateAndShowLobbyWindow();

	std::vector<OtherPlayer*> players = _lobby.GetPlayersInLobby();
	GtkTreeIter    iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
	gtk_label_set_text(runner.label_lobbyname, _lobby.Name().c_str());

	for (auto it = players.begin(); it != players.end(); ++it){
		OtherPlayer* p = *it;

		gtk_list_store_append(GTK_LIST_STORE(model), &iter);

		std::string playername = p->Name();
		uint32_t playerguid = p->GUID();

		gtk_list_store_set (GTK_LIST_STORE(model), &iter,
							COLUMN_PLAYER_NAME, playername.c_str(),
							COLUMN_PLAYER_READY, false,
							COLUMN_PLAYER_ID, playerguid,
							-1);
	}


}