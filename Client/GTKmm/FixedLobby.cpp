//
// Created by tino on 27/11/17.
//

#include "FixedLobby.h"


FixedLobby::FixedLobby() : fire_pguid(-1), water_pguid(-1),  ground_pguid(-1), air_pguid(-1)
{

}

FixedLobby::~FixedLobby(){

}

void FixedLobby::Set(const Glib::RefPtr<Gtk::Builder> &refBuilder) {
    refBuilder->get_widget("fixed_lobby", fixed);
    refBuilder->get_widget("treeview_lobbyPlayers", treeview);
    refBuilder->get_widget("button_lobbyReady", button_ready);
    refBuilder->get_widget("button_leaveLobby", button_leave);
    refBuilder->get_widget("combobox_maps", combobox_maps);
    refBuilder->get_widget("label_lobbyname", label_lobbyname);
    refBuilder->get_widget("radio_fire", toggle_fire);
    refBuilder->get_widget("radio_air", toggle_air);
    refBuilder->get_widget("radio_water", toggle_water);
    refBuilder->get_widget("radio_ground", toggle_ground);

    toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);

    store_players = Gtk::ListStore::create(columns_players);
    treeview->set_model(store_players);
    treeview->append_column("Name", columns_players.m_col_player_name);
    treeview->append_column("", columns_players.m_col_player_ready);


    store_maps = Gtk::ListStore::create(columns_maps);
    combobox_maps->set_model(store_maps);
    combobox_maps->pack_start(columns_maps.m_col_map_name);

    //faltan los spells
}

void FixedLobby::AddPlayer(OtherPlayer &player){
    Gtk::TreeModel::iterator iter = store_players->append();
    Gtk::TreeModel::Row row = *iter;
    row[columns_players.m_col_player_name] = player.Name();
    row[columns_players.m_col_player_id] = player.GUID();
    row[columns_players.m_col_player_ready] = "NOT READY";
}

void FixedLobby::RemovePlayer(OtherPlayer &player){
    typedef Gtk::TreeModel::Children type_children;
    type_children children = treeview->get_model()->children();
    for(type_children::iterator iter = children.begin();
        iter != children.end();)
    {
        Gtk::TreeModel::Row row = *iter;
        if (row.get_value(columns_players.m_col_player_id) == player.GUID()){
            iter = store_players->erase(iter);
            return;
        } else {
            ++iter;
        }
    }
}

void FixedLobby::RemoveAllPlayers(){
    typedef Gtk::TreeModel::Children type_children;
    type_children children = treeview->get_model()->children();
    for(type_children::iterator iter = children.begin();
        iter != children.end();)
    {
        iter = store_players->erase(iter);
    }
}

void FixedLobby::SetPlayerReadyStatus(uint playerGuid, bool ready){

    typedef Gtk::TreeModel::Children type_children;
    type_children children = treeview->get_model()->children();
    for(type_children::iterator iter = children.begin();
        iter != children.end(); ++iter)
    {
        Gtk::TreeModel::Row row = *iter;
        uint pguid = row.get_value(columns_players.m_col_player_id); 
        if (pguid == playerGuid){
            row[columns_players.m_col_player_ready] = ready ? "READY" : "NOT READY";
        }
    }
}

void FixedLobby::AddMe(std::string myname, uint guid){
    Gtk::TreeModel::iterator iter = store_players->append();
    Gtk::TreeModel::Row row = *iter;
    row[columns_players.m_col_player_name] = myname;
    row[columns_players.m_col_player_id] = guid;
    row[columns_players.m_col_player_ready] = "NOT READY";
}
