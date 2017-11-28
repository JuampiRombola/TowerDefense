#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification(Lobby& lobby)
: _lobby(lobby)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(GTKmmRunner& runner){
    runner.fixed_lobby.label_lobbyname->set_text(_lobby.Name());
    runner.box->remove(*runner.fixed_lobbies.fixed);
    runner.box->add(*runner.fixed_lobby.fixed);


    runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_water->set_sensitive(true);
    runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_water->set_sensitive(true);
    runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_air->set_sensitive(true);
    runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_ground->set_sensitive(true);



    runner.fixed_lobby.RemoveAllPlayers();

    auto ps = _lobby.GetOtherPlayersInLobby();
    for (auto it = ps.begin(); it != ps.end(); ++it)
        runner.fixed_lobby.AddPlayer(*(*it));

    runner.fixed_lobby.AddMe(runner.lobbyManager->myName, runner.lobbyManager->myGuid);

    uint myguid = runner.lobbyManager->myGuid;
    int fguid = _lobby.firePlayerGUID();
    int wguid = _lobby.waterPlayerGUID();
    int gguid = _lobby.groundPlayerGUID();
    int aguid = _lobby.airPlayerGUID();


    bool wsensitive = true;
    bool gsensitive = true;
    bool fsensitive = true;
    bool asensitive = true;

    if (fguid > 0){
        fsensitive = (fguid == myguid);
        runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.fire_pguid = fguid;
    }

    if (wguid > 0){
        wsensitive = (wguid == myguid);
        runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.water_pguid = wguid;
    }

    if (gguid > 0){
        gsensitive = (gguid == myguid);
        runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.ground_pguid = gguid;
    }

    if (aguid > 0){
        asensitive = (aguid == myguid);
        runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.air_pguid = aguid;
    }

    runner.fixed_lobby.toggle_fire->set_sensitive(fsensitive);
    runner.fixed_lobby.toggle_water->set_sensitive(wsensitive);
    runner.fixed_lobby.toggle_ground->set_sensitive(gsensitive);
    runner.fixed_lobby.toggle_air->set_sensitive(asensitive);

    runner.fixed_lobby.combobox_changed_signal.block();
    runner.fixed_lobby.combobox_maps->set_active(_lobby.pickedMapId);
    runner.fixed_lobby.combobox_changed_signal.unblock();

	//gtk_widget_hide (GTK_WIDGET(runner.window_global));
/*
	g_object_ref(runner.grid_lobbies);
	gtk_container_remove(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobbies));
	gtk_container_add(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobby));



	g_signal_handler_block(runner.check_air, runner.check_air_handler_id);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner.check_air), false);
	g_signal_handler_unblock(runner.check_air, runner.check_air_handler_id);

	g_signal_handler_block(runner.check_ground, runner.check_ground_handler_id);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner.check_ground), false);
	g_signal_handler_unblock(runner.check_ground, runner.check_ground_handler_id);

	g_signal_handler_block(runner.check_fire, runner.check_fire_handler_id);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner.check_fire), false);
	g_signal_handler_unblock(runner.check_fire, runner.check_fire_handler_id);

	g_signal_handler_block(runner.check_water, runner.check_water_handler_id);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner.check_water), false);
	g_signal_handler_unblock(runner.check_water, runner.check_water_handler_id);


	g_signal_handler_block(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);
	gtk_combo_box_set_active(runner.combobox_maps, _lobby.pickedMapId);
	g_signal_handler_unblock(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);


	std::vector<OtherPlayer*> players = _lobby.GetOtherPlayersInLobby();
	GtkTreeIter    iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
	gtk_label_set_text(runner.label_lobbyname, _lobby.Name().c_str());
	
	gtk_list_store_clear(GTK_LIST_STORE(model));

	for (auto it = players.begin(); it != players.end(); ++it){
		OtherPlayer* p = *it;

		gtk_list_store_append(GTK_LIST_STORE(model), &iter);

		std::string playername = p->Name();
		uint32_t playerguid = p->GUID();

		gtk_list_store_set (GTK_LIST_STORE(model), &iter,
							COLUMN_PLAYER_NAME, playername.c_str(),
							COLUMN_PLAYER_READY, false,
							COLUMN_PLAYER_ID, playerguid,
							-1);
	}

	GtkCheckButton* button;
	gulong handler;

	if (_lobby.FireIsPicked()){
		button = runner.check_fire;
		handler = runner.check_fire_handler_id;
		g_signal_handler_block(button, handler);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), true);
		gtk_widget_set_sensitive (GTK_WIDGET(button), false);
		g_signal_handler_unblock(button, handler);
	}

	if (_lobby.WaterIsPicked()){
		button = runner.check_water;
		handler = runner.check_water_handler_id;
		g_signal_handler_block(button, handler);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), true);
		gtk_widget_set_sensitive (GTK_WIDGET(button), false);
		g_signal_handler_unblock(button, handler);
	}

	if (_lobby.GroundIsPicked()){
		button = runner.check_ground;
		handler = runner.check_ground_handler_id;
		g_signal_handler_block(button, handler);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), true);
		gtk_widget_set_sensitive (GTK_WIDGET(button), false);
		g_signal_handler_unblock(button, handler);
	}

	if (_lobby.AirIsPicked()){
		button = runner.check_air;
		handler = runner.check_air_handler_id;
		g_signal_handler_block(button, handler);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), true);
		gtk_widget_set_sensitive (GTK_WIDGET(button), false);
		g_signal_handler_unblock(button, handler);
	}

*/
}