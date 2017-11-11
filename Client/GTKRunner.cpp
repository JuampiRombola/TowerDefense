#include "GTKRunner.h"
#include "include/NetCommands/LogInCommand.h"
#include "include/GTKNotifications/GTKNotification.h"
#include "include/NetCommands/GetLobbiesCommand.h"
#include "include/NetCommands/CreateLobbyCommand.h"
#include <iostream>
#include <gtk/gtk.h>

void GTKRunner::ShutdownGTK()
{
    gtk_main_quit();
}



void GTKRunner::newLobby_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* lobbyname = gtk_entry_get_text( runner->entry_newLobbyName );
    std::string s = std::string(lobbyname);
    runner->dispatcher->QueueCommand(new CreateLobbyCommand(s));
}
void GTKRunner::joinLobby_clicked(GtkWidget* widget, gpointer data){

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


void GTKRunner::LogInSuccess(){
    gtk_widget_hide (GTK_WIDGET(window_login));
    gtk_widget_show (GTK_WIDGET(window_lobbies));
    this->dispatcher->QueueCommand(new GetLobbiesCommand());
}

void GTKRunner::LogInFailed(){
    MessageBox("Log in failed");
}

void GTKRunner::connect_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
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

void GTKRunner::Run(int* argc, char***argv){
    GtkBuilder      *builder;

    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);
    this->window_connect = GTK_WINDOW(gtk_builder_get_object (builder, "window_connect"));
    this->window_login = GTK_WINDOW(gtk_builder_get_object (builder, "window_login"));
    this->window_lobbies = GTK_WINDOW(gtk_builder_get_object (builder, "window_lobbies"));
    GtkWidget* button_connect = GTK_WIDGET (gtk_builder_get_object (builder, "button_connect"));
    GtkWidget* button_login = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
    GtkWidget* button_newLobby = GTK_WIDGET (gtk_builder_get_object (builder, "button_newLobby"));
    GtkWidget* button_joinLobby = GTK_WIDGET (gtk_builder_get_object (builder, "button_joinLobby"));
    this->entry_ip = GTK_ENTRY(gtk_builder_get_object(builder, "entry_ip"));
    this->entry_port = GTK_ENTRY(gtk_builder_get_object(builder, "entry_port"));
    this->entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));
    this->entry_newLobbyName = GTK_ENTRY(gtk_builder_get_object(builder, "entry_newLobbyName"));

    this->listbox_lobbies = GTK_LIST_BOX(gtk_builder_get_object(builder, "listbox_lobbies"));
    this->list_store_lobbies = gtk_list_store_new (N_COLUMNS,
                                                   G_TYPE_STRING,
                                                   G_TYPE_INT,
                                                   G_TYPE_BOOLEAN);

    //liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    g_signal_connect (button_connect, "clicked", G_CALLBACK(GTKRunner::connect_clicked), this);
    g_signal_connect (button_login, "clicked", G_CALLBACK(GTKRunner::login_clicked), this);
    g_signal_connect (button_newLobby, "clicked", G_CALLBACK(GTKRunner::newLobby_clicked), this);
    g_signal_connect (button_joinLobby, "clicked", G_CALLBACK(GTKRunner::joinLobby_clicked), this);
    g_signal_connect (this->window_connect, "destroy", G_CALLBACK (GTKRunner::ShutdownGTK), this);
    g_signal_connect (this->window_login, "destroy", G_CALLBACK (GTKRunner::ShutdownGTK), this);

    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (GTK_WIDGET(this->window_connect));
    g_idle_add(notification_check, this);
    gtk_main ();
}
