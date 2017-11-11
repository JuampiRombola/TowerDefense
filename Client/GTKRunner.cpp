#include "GTKRunner.h"
#include "include/NetCommands/LogInCommand.h"
#include "include/GTKNotifications/GTKNotification.h"
#include <iostream>
#include <gtk/gtk.h>
#include <X11/Xlib.h>

void GTKRunner::destroy( GtkWidget *widget, gpointer   data )
{
    gtk_main_quit ();
}


void GTKRunner::login_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* name = gtk_entry_get_text( runner->entry_name );
    std::cout << "Name: " << name << '\n';
    std::string s = std::string(name);
    LogInCommand *command = new LogInCommand(s);
    runner->dispatcher->QueueCommand(command);
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

gpointer asyncUpdateUI(gpointer data) {
    GTKRunner* runner = (GTKRunner*) data;
    GTKNotification* gtkNoti = runner->GtkNotifications.Dequeue();
    while (gtkNoti != nullptr){
        gtkNoti->Execute(*runner);
        delete gtkNoti;
        gtkNoti = runner->GtkNotifications.Dequeue();
    }
}

void GTKRunner::connect_clicked(GtkWidget* widget, gpointer data){
    GTKRunner* runner = (GTKRunner*) data;
    const gchar* ip = gtk_entry_get_text( runner->entry_ip );
    const gchar* port = gtk_entry_get_text( runner->entry_port );
    std::cout << "IP: " << ip << ", port: " << port << "\n";
    runner->sock = new ClientSocket(ip, port);
    if (runner->sock->Connected()){
        runner->guiNotiQueue = new GUINotificationQueue();
        runner->lobbyManager = new ClientLobbyManager(*runner->guiNotiQueue, *runner->sock, *runner);
        runner->reciever = new NotificationReciever(*runner->sock, *runner->lobbyManager, *runner->guiNotiQueue, *runner);
        runner->dispatcher = new CommandDispatcher(*runner->sock);
        runner->dispatcher->Run();
        runner->reciever->Run();
        g_thread_new("thread", asyncUpdateUI, runner);
        gtk_widget_hide (GTK_WIDGET(runner->window_connect));
        gtk_widget_show (GTK_WIDGET(runner->window_login));
        std::cout << "Connect Succesful" << "  \n" ;
    }
    else
    {
        runner->MessageBox("Connect failed");
    }
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

    XInitThreads();
    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);
    this->window_connect = GTK_WINDOW(gtk_builder_get_object (builder, "window_connect"));
    this->window_login = GTK_WINDOW(gtk_builder_get_object (builder, "window_login"));
    button_connect = GTK_WIDGET (gtk_builder_get_object (builder, "button_connect"));
    button_login = GTK_WIDGET (gtk_builder_get_object (builder, "button_login"));
    this->entry_ip = GTK_ENTRY(gtk_builder_get_object(builder, "entry_ip"));
    this->entry_port = GTK_ENTRY(gtk_builder_get_object(builder, "entry_port"));
    this->entry_name = GTK_ENTRY(gtk_builder_get_object(builder, "entry_name"));

    //liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    g_signal_connect (button_connect, "clicked", G_CALLBACK(GTKRunner::connect_clicked), this);
    g_signal_connect (button_login, "clicked", G_CALLBACK(GTKRunner::login_clicked), this);
    g_signal_connect (this->window_connect, "destroy", G_CALLBACK (GTKRunner::destroy), this);
    g_signal_connect (this->window_login, "destroy", G_CALLBACK (GTKRunner::destroy), this);

    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (GTK_WIDGET(this->window_connect));
    gtk_main ();
}
