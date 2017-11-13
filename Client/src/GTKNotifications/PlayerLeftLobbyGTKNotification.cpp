//
// Created by tino on 12/11/17.
//

#include <gtk/gtktreemodel.h>
#include <gtk/gtktreeview.h>
#include "../../include/GTKNotifications/PlayerJoinedLobbyGTKNotification.h"
#include "../../GTKRunner.h"

PlayerJoinedLobbyGTKNotification::PlayerJoinedLobbyGTKNotification(OtherPlayer& player) : _player(player) {

}

PlayerJoinedLobbyGTKNotification::~PlayerJoinedLobbyGTKNotification() {

}
void PlayerJoinedLobbyGTKNotification::Execute(GTKRunner& runner){

    GtkTreeIter    iter;    G_TYPE_STRING, G_TYPE_UINT, G_TYPE_BOOLEAN

    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
    gtk_list_store_append(GTK_LIST_STORE(model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                        COLUMN_PLAYER_ID, _player.Name().c_str(),
                        COLUMN_PLAYER_READY, false,
                        COLUMN_PLAYER_NAME, _player.GUID(),
                        -1);
}
