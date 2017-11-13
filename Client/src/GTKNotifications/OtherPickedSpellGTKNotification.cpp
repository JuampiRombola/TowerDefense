#include <gtk/gtk.h>
#include "../../include/GTKNotifications/OtherPickedSpellGTKNotification.h"
#include "../../GTKRunner.h"
#include "../../../Common/Protocolo.h"

OtherPickedSpellGTKNotification::OtherPickedSpellGTKNotification(OtherPlayer& otherplayer, SPELL_TYPE spelltype, bool pick)
        : _otherPlayer(otherplayer),_spelltype(spelltype), _pick(pick) {

}

OtherPickedSpellGTKNotification::~OtherPickedSpellGTKNotification() {

}
void OtherPickedSpellGTKNotification::Execute(GTKRunner& runner){

    GtkCheckButton* button;
    gulong handler;
    switch(_spelltype){
        case SPELL_TYPE_AIR:
            button = runner.check_air;
            handler = runner.check_air_handler_id;
            break;
        case SPELL_TYPE_FIRE:
            button = runner.check_fire;
            handler = runner.check_fire_handler_id;
            break;
        case SPELL_TYPE_GROUND:
            button = runner.check_ground;
            handler = runner.check_ground_handler_id;
            break;
        case SPELL_TYPE_WATER:
            button = runner.check_water;
            handler = runner.check_water_handler_id;
            break;
    }

    g_signal_handler_block(button, handler);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), _pick);
    gtk_widget_set_sensitive (GTK_WIDGET(button), !_pick);
    g_signal_handler_unblock(button, handler);
    /*
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
    }*/
}
