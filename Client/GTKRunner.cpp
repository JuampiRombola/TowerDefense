#include "GTKRunner.h"
#include <iostream>
#include <gtk/gtk.h>

void GTKRunner::destroy( GtkWidget *widget, gpointer   data )
{
    gtk_main_quit ();
}


void GTKRunner::login_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* ip = gtk_entry_get_text( runner->entry_ip );
    const gchar* port = gtk_entry_get_text( runner->entry_port );
    std::cout << "IP: " << ip << ", port: " << port << "\n";
    runner->sock = new ClientSocket(ip, port);
    if (runner->sock->Connected()){
        std::cout << "Login Succesful" << "  \n" ;
        runner->guiNotiQueue = new GUINotificationQueue();
        runner->lobbyManager = new ClientLobbyManager(*runner->guiNotiQueue, *runner->sock);
        runner->reciever = new NotificationReciever(*runner->sock, *runner->lobbyManager, *runner->guiNotiQueue);
        runner->dispatcher = new CommandDispatcher(*runner->sock);
    }
    else
        std::cout << "Login failed\n" ;

}

void GTKRunner::connect_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* ip = gtk_entry_get_text( runner->entry_ip );
    const gchar* port = gtk_entry_get_text( runner->entry_port );
    std::cout << "IP: " << ip << ", port: " << port << "\n";
    runner->sock = new ClientSocket(ip, port);
    if (runner->sock->Connected()){
        gtk_widget_hide (runner->window_connect);
        gtk_widget_show (runner->window_login);
        std::cout << "Connect Succesful" << "  \n" ;
    }
    else
        std::cout << "Connect failed\n" ;
    //GtkTreeIter   iter;
    //gtk_list_store_append(liststore, &iter);

    /* Fill fields with some data */
    //gtk_list_store_set (liststore, &iter, 0, 'J', -1);


}


GTKRunner::GTKRunner() : OK (false) {

}

GTKRunner::~GTKRunner() {

}

void GTKRunner::Run(int* argc, char***argv){
    GtkBuilder      *builder;
    GtkWidget       *button_connect;
    GtkWidget       *button_login;

    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);
    this->window_connect = GTK_WIDGET (gtk_builder_get_object (builder, "window_connect"));
    this->window_login = GTK_WIDGET (gtk_builder_get_object (builder, "window_login"));
    button_connect = GTK_WIDGET (gtk_builder_get_object (builder, "button_connect"));
    button_login = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
    this->entry_ip = GTK_ENTRY(gtk_builder_get_object(builder, "entry_ip"));
    this->entry_port = GTK_ENTRY(gtk_builder_get_object(builder, "entry_port"));

    //liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    g_signal_connect (button_connect, "clicked", G_CALLBACK(GTKRunner::connect_clicked), this);
    g_signal_connect (button_login, "clicked", G_CALLBACK(GTKRunner::login_clicked), this);
    g_signal_connect (this->window_connect, "destroy", G_CALLBACK (GTKRunner::destroy), this);
    g_signal_connect (this->window_login, "destroy", G_CALLBACK (GTKRunner::destroy), this);

    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (this->window_connect);
    gtk_main ();
}
