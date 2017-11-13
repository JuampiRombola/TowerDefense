//
// Created by tino on 12/11/17.
//

#include <gtk/gtk.h>
#include "../../include/GTKNotifications/PlayerLeftLobbyGTKNotification.h"
#include "../../GTKRunner.h"

PlayerLeftLobbyGTKNotification::PlayerLeftLobbyGTKNotification(OtherPlayer& player) : _player(player) {

}

PlayerLeftLobbyGTKNotification::~PlayerLeftLobbyGTKNotification() {

}
void PlayerLeftLobbyGTKNotification::Execute(GTKRunner& runner){
    bool found = false;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
    gboolean valid = gtk_tree_model_get_iter_first (model, &iter);
    while (valid && !found)
    {
        gint playerGuid;
        gtk_tree_model_get (model, &iter, COLUMN_PLAYER_ID, &playerGuid, -1);
        if (playerGuid == _player.GUID()){
            found = true;
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
        }
        valid = gtk_tree_model_iter_next (model, &iter);
    }
}
