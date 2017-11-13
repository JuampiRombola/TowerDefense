#include <gtk/gtk.h>
#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../GTKRunner.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification
(Lobby& lobby)
: _lobby(lobby)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(GTKRunner& runner){
	gtk_widget_hide (GTK_WIDGET(runner.window_lobbies));

	runner.CreateAndShowLobbyWindow();

	std::vector<OtherPlayer*> players = _lobby.GetOtherPlayersInLobby();
	GtkTreeIter    iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner.treeview_lobbyPlayers);
	gtk_label_set_text(runner.label_lobbyname, _lobby.Name().c_str());

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


}