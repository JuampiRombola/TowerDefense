#include "GTKRunner.h"
#include "include/NetCommands/LogInCommand.h"
#include "include/GTKNotifications/GTKNotification.h"
#include "include/NetCommands/CreateLobbyCommand.h"
#include "include/NetCommands/JoinLobbyCommand.h"
#include "include/NetCommands/LeaveLobbyCommand.h"
#include "include/NetCommands/PlayerIsReadyCommand.h"
#include "include/NetCommands/PickSpellCommand.h"
#include "include/NetCommands/PickMapCommand.h"
#include <iostream>
#include <gtk/gtk.h>

void GTKRunner::ShutdownGTK()
{
    gtk_main_quit();
}

void GTKRunner::_LobbyWindowClosed(GtkWidget* widget, gpointer data)
{
    GTKRunner* runner = (GTKRunner*) data;
    runner->dispatcher->QueueCommand(new LeaveLobbyCommand());

    GtkTreeIter    iter;
    GtkTreeModel *model = gtk_tree_view_get_model (runner->treeview_lobbies);
    gtk_list_store_clear (GTK_LIST_STORE(model));

    std::vector<Lobby*> lobbies = runner->lobbyManager->GetLobbies();

    for (auto it = lobbies.begin(); it != lobbies.end(); ++it){
        Lobby* l = *it;
        gtk_list_store_append(GTK_LIST_STORE(model), &iter);
        gtk_list_store_set (GTK_LIST_STORE(model), &iter,
                            COLUMN_LOBBY_NAME, l->Name().c_str(),
                            COLUMN_LOBBY_ID, l->GUID(),
                            -1);
    }
}


void GTKRunner::_AirCheckboxToggled(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    g_signal_handler_block(widget, runner->check_air_handler_id);
    gboolean active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
    if (active){
        //Lo checkeo entonces lo deschequeo.
        //Porque para asegurar el check esperamos la notificacion del servidor
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_air), FALSE);
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_AIR, true));
        //player picked air power
    } else {
        //Lo mismo..
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_AIR, false));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_air), TRUE);
        //player unpicked air power
    }
    g_signal_handler_unblock(widget, runner->check_air_handler_id);
}

void GTKRunner::_GroundCheckboxToggled(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    g_signal_handler_block(widget, runner->check_ground_handler_id);
    gboolean active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
    if (active){
        //Lo checkeo entonces lo deschequeo.
        //Porque para asegurar el check esperamos la notificacion del servidor
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_ground), FALSE);
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_GROUND, true));
        //player picked ground power
    } else {
        //Lo mismo..
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_GROUND, false));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_ground), TRUE);
        //player unpicked ground power
    }
    g_signal_handler_unblock(widget, runner->check_ground_handler_id);
}


void GTKRunner::_FireCheckboxToggled(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    g_signal_handler_block(widget, runner->check_fire_handler_id);
    gboolean active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
    if (active){
        //Lo checkeo entonces lo deschequeo.
        //Porque para asegurar el check esperamos la notificacion del servidor
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_fire), FALSE);
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_FIRE, true));
        //player picked ground power
    } else {
        //Lo mismo..
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_FIRE, false));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_fire), TRUE);
        //player unpicked ground power
    }
    g_signal_handler_unblock(widget, runner->check_fire_handler_id);
}


void GTKRunner::_WaterCheckboxToggled(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    g_signal_handler_block(widget, runner->check_water_handler_id);
    gboolean active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
    if (active){
        //Lo checkeo entonces lo deschequeo.
        //Porque para asegurar el check esperamos la notificacion del servidor
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_water), FALSE);
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_WATER, true));
        //player picked ground power
    } else {
        //Lo mismo..
        runner->dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_WATER, false));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(runner->check_water), TRUE);
        //player unpicked ground power
    }
    g_signal_handler_unblock(widget, runner->check_water_handler_id);
}


void GTKRunner::newLobby_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* lobbyname = gtk_entry_get_text( runner->entry_newLobbyName );
    std::string s = std::string(lobbyname);
    runner->dispatcher->QueueCommand(new CreateLobbyCommand(s));
}
void GTKRunner::joinLobby_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    GtkTreeSelection* selection = gtk_tree_view_get_selection(runner->treeview_lobbies);
    GtkTreeModel *model;
    gint lobbyId;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected (selection, &model, &iter)){
        gtk_tree_model_get(model, &iter, COLUMN_LOBBY_ID, &lobbyId, -1);
        runner->dispatcher->QueueCommand(new JoinLobbyCommand(lobbyId));
    }
}

void GTKRunner::leaveLobby_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;

    runner->dispatcher->QueueCommand(new LeaveLobbyCommand());


}
void GTKRunner::lobbyReady_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    runner->dispatcher->QueueCommand(new PlayerIsReadyCommand());
}

void GTKRunner::login_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* name = gtk_entry_get_text( runner->entry_name );
    std::string s = std::string(name);
    runner->dispatcher->QueueCommand(new LogInCommand(s));
}


void GTKRunner::map_combobox_selection_changed(GtkWidget *widget, gpointer data) {
    GTKRunner* runner = (GTKRunner*) data;
    uint i = gtk_combo_box_get_active(runner->combobox_maps);
    runner->dispatcher->QueueCommand(new PickMapCommand(i));
    g_signal_handler_block(widget, runner->combo_box_maps_changed_handler_id);
    gtk_combo_box_set_active(runner->combobox_maps, -1);
    g_signal_handler_unblock(widget, runner->combo_box_maps_changed_handler_id);

}




void GTKRunner::MessageBox(std::string s){
    GtkDialogFlags flags;
    auto dialog = gtk_message_dialog_new (this->window_global,
                                          flags,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_CLOSE,
                                          s.c_str(), "%s");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void GTKRunner::connect_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* ip = gtk_entry_get_text( runner->entry_ip );
    const gchar* port = gtk_entry_get_text( runner->entry_port );
    runner->sock = new ClientSocket(ip, port);
    if (runner->sock->Connected()){
        runner->lobbyManager = new ClientLobbyManager(*runner->sock, *runner);
        runner->dispatcher = new CommandDispatcher(*runner->sock);
        runner->reciever = new NotificationReciever(*runner->sock, *runner->lobbyManager, *runner, *(runner->dispatcher));
        runner->dispatcher->Run();
        runner->reciever->Run();
        g_object_ref(runner->grid_connect);
        gtk_container_remove(GTK_CONTAINER(runner->box1), GTK_WIDGET(runner->grid_connect));
        gtk_container_add(GTK_CONTAINER(runner->box1), GTK_WIDGET(runner->grid_login));
    }
    else
    {
        runner->MessageBox("Connect failed");
    }
}


GTKRunner::GTKRunner() : sock(nullptr),
lobbyManager(nullptr),
reciever(nullptr),
dispatcher(nullptr) ,OK (false) {
}

GTKRunner::~GTKRunner() {
    if (!OK)
    {
        if (sock != nullptr){
            delete sock;
            sock = nullptr;
        }
        if (reciever != nullptr){
            delete reciever;
            reciever = nullptr;
        }
        if (dispatcher != nullptr){
            delete dispatcher;
            dispatcher = nullptr;
        }
        if (lobbyManager != nullptr){
            delete lobbyManager;
            lobbyManager = nullptr;
        }
    }
}


gboolean GTKRunner::notification_check(gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    GTKNotification* gtkNoti = runner->gtkNotifications.Dequeue();
    while (gtkNoti != nullptr){
        gtkNoti->Execute(*runner);
        delete gtkNoti;
        gtkNoti = runner->gtkNotifications.Dequeue();
    }
    return false;
}


void GTKRunner::_InitLobbiesTreeView()
{
    GtkCellRenderer     *renderer;

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (this->treeview_lobbies,
                                                 -1,
                                                 "Lobby Name",
                                                 renderer,
                                                 "text", COLUMN_LOBBY_NAME,
                                                 NULL);

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (this->treeview_lobbies,
                                                 -1,
                                                 "Lobby Id",
                                                 renderer,
                                                 "text", COLUMN_LOBBY_ID,
                                                 NULL);

    auto store = gtk_list_store_new (LOBBIES_N_COLUMNS, G_TYPE_STRING, G_TYPE_INT);

    gtk_tree_view_set_model (this->treeview_lobbies, GTK_TREE_MODEL(store));

    g_object_unref (store);
}

void GTKRunner::_InitLobbyPlayersTreeView()
{
    GtkCellRenderer     *renderer;

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (this->treeview_lobbyPlayers,
                                                 -1,
                                                 "Player Name",
                                                 renderer,
                                                 "text", COLUMN_PLAYER_NAME,
                                                 NULL);

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (this->treeview_lobbyPlayers,
                                                 -1,
                                                 "Player Id",
                                                 renderer,
                                                 "text", COLUMN_PLAYER_ID,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (this->treeview_lobbyPlayers,
                                                 -1,
                                                 "Ready",
                                                 renderer,
                                                 "text", COLUMN_PLAYER_READY,
                                                 NULL);

    auto store = gtk_list_store_new (LOBBY_PLAYERS_N_COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_BOOLEAN);

    gtk_tree_view_set_model (this->treeview_lobbyPlayers, GTK_TREE_MODEL(store));

    g_object_unref (store);
}


void GTKRunner::_InitMapsComboBox() {
    //auto store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_UINT);
    auto store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_UINT);

    gtk_combo_box_set_model (this->combobox_maps, GTK_TREE_MODEL(store));

    GtkCellRenderer* column =  gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(this->combobox_maps), column, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(this->combobox_maps), column,
                                   "text", 0, NULL);
    g_object_unref (store);
}


void GTKRunner::Run(int* argc, char***argv){
    GtkBuilder      *builder;

    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);

    this->window_global = GTK_WINDOW(gtk_builder_get_object (builder, "window_global"));
    g_signal_connect (this->window_global, "destroy", G_CALLBACK(GTKRunner::ShutdownGTK), this);

    this->grid_connect = GTK_GRID(gtk_builder_get_object(builder, "grid_connect"));
    this->grid_login = GTK_GRID(gtk_builder_get_object(builder, "grid_login"));
    this->grid_lobbies = GTK_GRID(gtk_builder_get_object(builder, "grid_lobbies"));
    this->grid_lobby = GTK_GRID(gtk_builder_get_object(builder, "grid_lobby"));
    this->box1 = GTK_BOX(gtk_builder_get_object(builder, "box1"));

    GtkWidget* button_connect = GTK_WIDGET (gtk_builder_get_object (builder, "button_connect"));
    GtkWidget* button_login = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
    GtkWidget* button_newLobby = GTK_WIDGET (gtk_builder_get_object (builder, "button_newLobby"));
    GtkWidget* button_joinLobby = GTK_WIDGET (gtk_builder_get_object (builder, "button_joinLobby"));

    g_signal_connect (button_connect, "clicked", G_CALLBACK(GTKRunner::connect_clicked), this);
    g_signal_connect (button_login, "clicked", G_CALLBACK(GTKRunner::login_clicked), this);
    g_signal_connect (button_newLobby, "clicked", G_CALLBACK(GTKRunner::newLobby_clicked), this);
    g_signal_connect (button_joinLobby, "clicked", G_CALLBACK(GTKRunner::joinLobby_clicked), this);


    this->entry_ip = GTK_ENTRY(gtk_builder_get_object(builder, "entry_ip"));
    this->entry_port = GTK_ENTRY(gtk_builder_get_object(builder, "entry_port"));
    this->entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    this->entry_newLobbyName = GTK_ENTRY(gtk_builder_get_object(builder, "entry_newLobbyName"));

    this->treeview_lobbies = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview_lobbies"));

    this->_InitLobbiesTreeView();

    this->check_air = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "check_air"));
    this->check_fire = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "check_fire"));
    this->check_ground = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "check_ground"));
    this->check_water = GTK_CHECK_BUTTON(gtk_builder_get_object (builder, "check_water"));

    this->check_air_handler_id = g_signal_connect (this->check_air, "toggled", G_CALLBACK(GTKRunner::_AirCheckboxToggled), this);
    this->check_ground_handler_id = g_signal_connect (this->check_ground, "toggled", G_CALLBACK(GTKRunner::_GroundCheckboxToggled), this);
    this->check_fire_handler_id = g_signal_connect (this->check_fire, "toggled", G_CALLBACK(GTKRunner::_FireCheckboxToggled), this);
    this->check_water_handler_id = g_signal_connect (this->check_water, "toggled", G_CALLBACK(GTKRunner::_WaterCheckboxToggled), this);

    GtkWidget* button_leaveLobby = GTK_WIDGET (gtk_builder_get_object (builder, "button_leaveLobby"));
    GtkWidget* button_lobbyReady = GTK_WIDGET (gtk_builder_get_object (builder, "button_lobbyReady"));
    g_signal_connect (button_leaveLobby, "clicked", G_CALLBACK(GTKRunner::leaveLobby_clicked), this);
    g_signal_connect (button_lobbyReady, "clicked", G_CALLBACK(GTKRunner::lobbyReady_clicked), this);
    this->treeview_lobbyPlayers = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview_lobbyPlayers"));
    this->label_lobbyname = GTK_LABEL(gtk_builder_get_object(builder, "label_lobbyname"));
    this->_InitLobbyPlayersTreeView();
    this->combobox_maps = GTK_COMBO_BOX(gtk_builder_get_object(builder, "combobox_maps"));

    this->combo_box_maps_changed_handler_id = g_signal_connect (this->combobox_maps, "changed", G_CALLBACK(GTKRunner::map_combobox_selection_changed), this);
    _InitMapsComboBox();

    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));



//    gtk_window_set_default_size(GTK_WINDOW(this->window_global), 640, 360);
    gtk_window_set_default_size(GTK_WINDOW(this->window_global), 800, 600);
    g_object_ref(this->grid_login);
    g_object_ref(this->grid_lobbies);
    g_object_ref(this->grid_lobby);
    gtk_container_remove(GTK_CONTAINER(this->box1), GTK_WIDGET(this->grid_login));
    gtk_container_remove(GTK_CONTAINER(this->box1), GTK_WIDGET(this->grid_lobbies));
    gtk_container_remove(GTK_CONTAINER(this->box1), GTK_WIDGET(this->grid_lobby));
    gtk_widget_show (GTK_WIDGET(this->window_global));
    gtk_main ();
}
