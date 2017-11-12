

#include <gtk/gtk.h>
#include "../../include/GTKNotifications/NewLobbyGTKNotification.h"
#include "../../GTKRunner.h"


NewLobbyGTKNotification::NewLobbyGTKNotification(Lobby& lobby) : _lobby(lobby) {
	
}

NewLobbyGTKNotification::~NewLobbyGTKNotification(){
	
}

void NewLobbyGTKNotification::Execute(GTKRunner& runner){

    GtkTreeIter    iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbies);
    gtk_list_store_append(GTK_LIST_STORE(model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                        COLUMN_LOBBY_NAME, _lobby.Name().c_str(),
                        COLUMN_LOBBY_ID, _lobby.GUID(),
                        -1);
}
