//
// Created by tino on 11/11/17.
//

#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


LogInSuccessGtkNotification::LogInSuccessGtkNotification(std::vector<Lobby*>& lobbies, std::string myname)
        : _lobbies(lobbies), _myname(myname){

}

LogInSuccessGtkNotification::~LogInSuccessGtkNotification(){

}

void LogInSuccessGtkNotification::Execute(GTKmmRunner& runner){


    runner.box->remove(*runner.fixed_login.fixed);
    runner.box->add(*runner.fixed_lobbies.fixed);
    runner.fixed_lobbies.SetMyName(_myname);


    for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
        uint pamount = (*it)->GetOtherPlayersInLobby().size();
        runner.fixed_lobbies.NewLobby((*it)->Name(), (*it)->GUID());
        runner.fixed_lobbies.UpdateLobbyPlayerCount((*it)->GUID(), pamount);
    }


    for (auto it = runner.lobbyManager->maps.begin(); it != runner.lobbyManager->maps.end(); ++it){
        std::tuple<std::string, uint32_t> tup = *it;
        std::string mapname = std::get<0>(tup);
        uint32_t mapid = std::get<1>(tup);

        auto row = *(runner.fixed_lobby.store_maps->append());
        row[runner.fixed_lobby.columns_maps.m_col_map_name] = mapname;
        row[runner.fixed_lobby.columns_maps.m_col_map_id] = mapid;
    }



    /*
    g_object_ref(runner.grid_login);
    gtk_container_remove(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_login));
    gtk_container_add(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobbies));

    GtkTreeIter    iter;

    GtkTreeModel* model = gtk_combo_box_get_model(runner.combobox_maps);
    for (auto it = runner.lobbyManager->maps.begin(); it != runner.lobbyManager->maps.end(); ++it){
        std::tuple<std::string, uint32_t> tup = *it;
        std::string mapname = std::get<0>(tup);
        uint32_t mapid = std::get<1>(tup);
        gtk_list_store_append(GTK_LIST_STORE(model), &iter);
        gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                            0, mapname.c_str(),
                            1, mapid,
                            -1);
    }
    g_signal_handler_block(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);
    gtk_combo_box_set_active(runner.combobox_maps, -1);
    g_signal_handler_unblock(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);*/
}