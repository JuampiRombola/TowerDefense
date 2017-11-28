#include "../../include/GTKNotifications/PickSpellGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"
#include "../../../Common/Protocolo.h"

PickSpellGTKNotification::PickSpellGTKNotification(uint pguid, SPELL_TYPE spelltype)
        : _pguid(pguid),_spelltype(spelltype) {

}

PickSpellGTKNotification::~PickSpellGTKNotification() {

}
void PickSpellGTKNotification::Execute(GTKmmRunner& runner){


    if (runner.fixed_lobby.water_pguid == _pguid){
        runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
        runner.fixed_lobby.toggle_water->set_sensitive(true);
        runner.fixed_lobby.water_pguid = -1;
    }
    if (runner.fixed_lobby.air_pguid == _pguid){
        runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
        runner.fixed_lobby.toggle_air->set_sensitive(true);
        runner.fixed_lobby.air_pguid = -1;
    }

    if (runner.fixed_lobby.ground_pguid == _pguid){
        runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
        runner.fixed_lobby.toggle_ground->set_sensitive(true);
        runner.fixed_lobby.ground_pguid = -1;
    }
    if (runner.fixed_lobby.fire_pguid == _pguid){
        runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
        runner.fixed_lobby.toggle_fire->set_sensitive(true);
        runner.fixed_lobby.fire_pguid = -1;
    }

    Gtk::ToggleButton* toset;

    switch(_spelltype){
        case SPELL_TYPE_AIR:
            runner.fixed_lobby.air_pguid = _pguid;
            toset = runner.fixed_lobby.toggle_air;
            break;
        case SPELL_TYPE_FIRE:
            runner.fixed_lobby.fire_pguid = _pguid;
            toset = runner.fixed_lobby.toggle_fire;
            break;
        case SPELL_TYPE_GROUND:
            runner.fixed_lobby.ground_pguid = _pguid;
            toset = runner.fixed_lobby.toggle_ground;
            break;
        case SPELL_TYPE_WATER:
            runner.fixed_lobby.water_pguid = _pguid;
            toset = runner.fixed_lobby.toggle_water;
            break;
    }


    toset->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
    toset->set_sensitive(runner.lobbyManager->myGuid == _pguid);



/*
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
    g_signal_handler_unblock(button, handler);*/
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
