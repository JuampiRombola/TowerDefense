#include "GTKRunner.h"
#include "include/NetCommands/LogInCommand.h"
#include "include/GTKNotifications/GTKNotification.h"
#include "include/NetCommands/CreateLobbyCommand.h"
#include "include/NetCommands/JoinLobbyCommand.h"
#include "include/NetCommands/LeaveLobbyCommand.h"
#include "include/NetCommands/PlayerIsReadyCommand.h"
#include <iostream>
#include <gtk/gtk.h>

void GTKRunner::_ShutdownGTK()
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

void GTKRunner::MessageBox(std::string s){
    GtkDialogFlags flags;
    auto dialog = gtk_message_dialog_new (this->window_login,
                                          flags,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_CLOSE,
                                          s.c_str(), "%s");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void GTKRunner::connect_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    std::string testep = runner->TEST;
    const gchar* ip = gtk_entry_get_text( runner->entry_ip );
    const gchar* port = gtk_entry_get_text( runner->entry_port );
    runner->sock = new ClientSocket(ip, port);
    if (runner->sock->Connected()){
        runner->lobbyManager = new ClientLobbyManager(*runner->sock, *runner);
        runner->reciever = new NotificationReciever(*runner->sock, *runner->lobbyManager, *runner);
        runner->dispatcher = new CommandDispatcher(*runner->sock);
        runner->dispatcher->Run();
        runner->reciever->Run();
        gtk_widget_hide (GTK_WIDGET(runner->window_connect));
        gtk_widget_show (GTK_WIDGET(runner->window_login));
        std::cout << "Connect Succesful" << "  \n" ;
    }
    else
    {
        runner->MessageBox("Connect failed");
    }
}


GTKRunner::GTKRunner() : OK (false) {
}

GTKRunner::~GTKRunner() {
    if (!OK){
        reciever->Stop();
        dispatcher->Stop();
        delete lobbyManager;
        delete reciever;
        delete dispatcher;
    }
}


gboolean notification_check(gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    GTKNotification* gtkNoti = runner->gtkNotifications.Dequeue();
    while (gtkNoti != nullptr){
        gtkNoti->Execute(*runner);
        delete gtkNoti;
        gtkNoti = runner->gtkNotifications.Dequeue();
    }
    return true;
}


void GTKRunner::InitLobbiesTreeView()
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

void GTKRunner::InitLobbyPlayersTreeView()
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

void GTKRunner::CreateAndShowLobbyWindow(){
    GtkBuilder* Lobbybuilder = gtk_builder_new ();
    gtk_builder_add_from_file (Lobbybuilder, "../Client/Lobby.glade", NULL);
    this->window_lobby = GTK_WINDOW(gtk_builder_get_object (Lobbybuilder, "window_lobby"));
    g_signal_connect (this->window_lobby, "destroy", G_CALLBACK(GTKRunner::_LobbyWindowClosed), this);
    GtkWidget* button_leaveLobby = GTK_WIDGET (gtk_builder_get_object (Lobbybuilder, "button_leaveLobby"));
    GtkWidget* button_lobbyReady = GTK_WIDGET (gtk_builder_get_object (Lobbybuilder, "button_lobbyReady"));
    g_signal_connect (button_leaveLobby, "clicked", G_CALLBACK(GTKRunner::leaveLobby_clicked), this);
    g_signal_connect (button_lobbyReady, "clicked", G_CALLBACK(GTKRunner::lobbyReady_clicked), this);
    this->treeview_lobbyPlayers = GTK_TREE_VIEW(gtk_builder_get_object(Lobbybuilder, "treeview_lobbyPlayers"));
    this->label_lobbyname = GTK_LABEL(gtk_builder_get_object(Lobbybuilder, "label_lobbyname"));
    this->InitLobbyPlayersTreeView();
    gtk_builder_connect_signals (Lobbybuilder, NULL);
    gtk_widget_show (GTK_WIDGET(this->window_lobby));
    g_object_unref (G_OBJECT (Lobbybuilder));
}

void GTKRunner::Run(int* argc, char***argv){
    GtkBuilder      *builder;

    gtk_init (argc, argv);





    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);
    this->window_connect = GTK_WINDOW(gtk_builder_get_object (builder, "window_connect"));
    this->window_login = GTK_WINDOW(gtk_builder_get_object (builder, "window_login"));
    this->window_lobbies = GTK_WINDOW(gtk_builder_get_object (builder, "window_lobbies"));
    g_signal_connect (this->window_connect, "destroy", G_CALLBACK(GTKRunner::_ShutdownGTK), this);
    g_signal_connect (this->window_login, "destroy", G_CALLBACK(GTKRunner::_ShutdownGTK), this);
    g_signal_connect (this->window_lobbies, "destroy", G_CALLBACK(GTKRunner::_ShutdownGTK), this);
    //g_signal_connect (this->window_lobby, "destroy", G_CALLBACK(GTKRunner::_LobbyWindowClosed), this);

    TEST = "SOMETEST";

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

    this->InitLobbiesTreeView();

    //liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (GTK_WIDGET(this->window_connect));
    g_idle_add(notification_check, this);
    gtk_main ();
}
