//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_FIXEDLOBBY_H
#define TOWERDEFENSE_FIXEDLOBBY_H


#include <gtkmm/fixed.h>
#include <gtkmm/builder.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/combobox.h>
#include <gtkmm/radiobutton.h>
#include "../include/Lobbies/OtherPlayer.h"


#ifndef LOBBY_COLUMNS
#define LOBBY_COLUMNS
class LobbyColumns : public Gtk::TreeModelColumnRecord
{
public:

    LobbyColumns()
    {
        add(m_col_player_name);
        add(m_col_player_id);
        add(m_col_player_ready);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_player_name;
    Gtk::TreeModelColumn<int> m_col_player_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_player_ready;
};
#endif


#ifndef MAP_COLUMNS
#define MAP_COLUMNS
class MapColumns : public Gtk::TreeModelColumnRecord
{
public:

    MapColumns ()
    {
        add(m_col_map_name);
        add(m_col_map_id);
    }

    Gtk::TreeModelColumn<Glib::ustring> m_col_map_name;
    Gtk::TreeModelColumn<uint> m_col_map_id;
};
#endif


class FixedLobby {
public:
    FixedLobby();
    ~FixedLobby();
    void Set(const Glib::RefPtr<Gtk::Builder> &refBuilder);

    Gtk::TreeView *treeview;
    Glib::RefPtr<Gtk::ListStore> store_players;
    LobbyColumns columns_players;

    Gtk::ComboBox* combobox_maps;
    Glib::RefPtr<Gtk::ListStore> store_maps;
    MapColumns columns_maps;

    Gtk::Button* button_ready;
    Gtk::Button* button_leave;
    Gtk::Fixed* fixed;
    Gtk::Label* label_lobbyname;

    Gtk::ToggleButton* toggle_fire;
    int fire_pguid;
    Gtk::ToggleButton* toggle_water;
    int water_pguid;
    Gtk::ToggleButton* toggle_ground;
    int ground_pguid;
    Gtk::ToggleButton* toggle_air;
    int air_pguid;

    sigc::connection combobox_changed_signal;

    void AddPlayer(OtherPlayer &player);
    void RemovePlayer(OtherPlayer &player);
    void RemoveAllPlayers();
    void SetPlayerReadyStatus(uint playerGuid, bool ready);
    void AddMe(std::string myname, uint guid);
};



#endif //TOWERDEFENSE_FIXEDLOBBY_H
