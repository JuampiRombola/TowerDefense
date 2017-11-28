//
// Created by tino on 27/11/17.
//

#include "FixedLobbies.h"


FixedLobbies::FixedLobbies() : store() {

}

FixedLobbies::~FixedLobbies() {

}

void FixedLobbies::Set(const Glib::RefPtr<Gtk::Builder> &refBuilder){
    refBuilder->get_widget("fixed_lobbies", fixed);
    refBuilder->get_widget("entry_newLobbyName", entry_newLobbyName);
    refBuilder->get_widget("button_newLobby", button_newLobby);
    refBuilder->get_widget("button_joinLobby", button_joinLobby);
    refBuilder->get_widget("treeview_lobbies", treeview);
    refBuilder->get_widget("label_myname", label_myname);


    store = Gtk::ListStore::create(columns);
    g_object_ref(store->gobj());

    treeview->set_model(store);
    treeview->append_column("Nombre", this->columns.m_col_lobbyname);
    treeview->append_column("Players", this->columns.m_col_lobby_player_amount);
}

void FixedLobbies::NewLobby(std::string name, uint guid) {
    Gtk::TreeModel::iterator iter = store->append();
    Gtk::TreeModel::Row row = *iter;
    row[columns.m_col_lobbyname] = name;
    row[columns.m_col_lobbyid] = guid;
    row[columns.m_col_lobby_player_amount] = 0;
}


void FixedLobbies::RemoveLobby(uint32_t lobbyGuid){
    typedef Gtk::TreeModel::Children type_children;
    type_children children = treeview->get_model()->children();
    for(type_children::iterator iter = children.begin();
        iter != children.end();)
    {
        Gtk::TreeModel::Row row = *iter;
        uint lguid = row.get_value(columns.m_col_lobbyid);
        if (lguid == lobbyGuid){
            iter = store->erase(iter);
        } else{
            ++iter;
        }
    }
}

void FixedLobbies::SetMyName(std::string &name) {
    label_myname->set_text(name);
}

int FixedLobbies::GetSelectedLobbyId(){
    Gtk::TreeModel::Row row = *(treeview->get_selection()->get_selected());
    if (row)
        return row.get_value(columns.m_col_lobbyid);
    else
        return -1;
}

void FixedLobbies::UpdateLobbyPlayerCount(uint guid, int amount){

    typedef Gtk::TreeModel::Children type_children;
    type_children children = treeview->get_model()->children();
    for(type_children::iterator iter = children.begin();
        iter != children.end(); ++iter)
    {
        Gtk::TreeModel::Row row = *iter;
        if (row.get_value(columns.m_col_lobbyid) == guid){
            uint actual = row[columns.m_col_lobby_player_amount];
            row[columns.m_col_lobby_player_amount] = actual + amount;
        }
    }
}