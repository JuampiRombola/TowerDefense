//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_FIXEDLOBBIES_H
#define TOWERDEFENSE_FIXEDLOBBIES_H


#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/fixed.h>
#include <gtkmm/entry.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>

#ifndef LOBBIES_COLUMNS
#define LOBBIES_COLUMNS
class LobbiesColumns : public Gtk::TreeModelColumnRecord
{
public:

    LobbiesColumns()
    {
        add(m_col_lobbyname);
        add(m_col_lobbyid);
        add(m_col_lobby_player_amount);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_lobbyname;
    Gtk::TreeModelColumn<uint> m_col_lobbyid;
    Gtk::TreeModelColumn<uint> m_col_lobby_player_amount;
};


#endif



class FixedLobbies {
public:
    FixedLobbies();
    ~FixedLobbies();


    Gtk::TreeView *treeview;
    Glib::RefPtr<Gtk::ListStore> store;
    LobbiesColumns columns;

    void SetMyName(std::string& name);

    Gtk::Label* label_myname;
    Gtk::Fixed* fixed;
    Gtk::Button* button_newLobby;
    Gtk::Button* button_joinLobby;
    Gtk::Entry* entry_newLobbyName;

    void NewLobby(std::string name, uint guid);

    void Set(const Glib::RefPtr<Gtk::Builder> &refBuilder);

    int GetSelectedLobbyId();

    void UpdateLobbyPlayerCount(uint lobbyGuid, int amount);

};

#endif //TOWERDEFENSE_FIXEDLOBBIES_H
