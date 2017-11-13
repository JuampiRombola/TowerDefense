//
// Created by tino on 12/11/17.
//

#include <gtk/gtk.h>
#include "../../include/GTKNotifications/PlayerJoinedLobbyGTKNotification.h"
#include "../../GTKRunner.h"

PlayerJoinedLobbyGTKNotification::PlayerJoinedLobbyGTKNotification(OtherPlayer& player) : _player(player) {

}

PlayerJoinedLobbyGTKNotification::~PlayerJoinedLobbyGTKNotification() {

}
void PlayerJoinedLobbyGTKNotification::Execute(GTKRunner& runner){

    GtkTreeIter    iter;

    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
    gtk_list_store_append(GTK_LIST_STORE(model), &iter);

    std::string playername = _player.Name();
    uint32_t playerguid = _player.GUID();
    
    gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                        COLUMN_PLAYER_NAME, playername.c_str(),
                        COLUMN_PLAYER_READY, false,
                        COLUMN_PLAYER_ID, playerguid,
                        -1);
}
