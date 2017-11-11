//
// Created by tino on 10/11/17.
//

#ifndef TOWERDEFENSE_GTKRUNNER_H
#define TOWERDEFENSE_GTKRUNNER_H
#include <gtk/gtk.h>
#include "include/ClientSocket.h"
#include "include/Lobbies/ClientLobbyManager.h"
#include "include/NotificationReciever.h"
#include "include/NetCommands/CommandDispatcher.h"
#include "include/SDLNotifications/GUINotificationQueue.h"
#include "../Server/include/ThreadSafeQueue.h"

class GTKNotification;

#ifndef __GTK_NOTIFICATION_QUEUE__
#define __GTK_NOTIFICATION_QUEUE__
template class ThreadSafeQueue<GTKNotification*>;
#endif

class GTKRunner {
private:
    static void destroy( GtkWidget *widget, gpointer   data );
    static void connect_clicked(GtkWidget* widget, gpointer data);
    static void login_clicked(GtkWidget* widget, gpointer data);
public:
    GTKRunner();
    ~GTKRunner();

    ThreadSafeQueue<GTKNotification*> GtkNotifications;
    GUINotificationQueue* guiNotiQueue;
    ClientLobbyManager* lobbyManager;
    NotificationReciever* reciever;
    CommandDispatcher* dispatcher;

    GtkWindow *window_connect;
    GtkWindow *window_login;

    bool OK;
    void MessageBox(std::string s);

    ClientSocket* sock;

    GtkEntry *entry_ip;
    GtkEntry *entry_port;
    GtkEntry *entry_name;

    void Run(int* argc, char***argv);
};


#endif //TOWERDEFENSE_GTKRUNNER_H
