//
// Created by tino on 10/11/17.
//

#ifndef TOWERDEFENSE_GTKRUNNER_H
#define TOWERDEFENSE_GTKRUNNER_H
#include <gtk/gtk.h>
#include "include/ClientSocket.h"
#include "include/Lobbies/ClientLobbyManager.h"
#include "include/GUINotifications/NotificationReciever.h"
#include "include/NetCommands/CommandDispatcher.h"
#include "include/GUINotifications/GUINotificationQueue.h"

class GTKRunner {
private:
    static void destroy( GtkWidget *widget, gpointer   data );
    static void connect_clicked(GtkWidget* widget, gpointer data);
    static void login_clicked(GtkWidget* widget, gpointer data);
public:
    GTKRunner();
    ~GTKRunner();

    GUINotificationQueue* guiNotiQueue;
    ClientLobbyManager* lobbyManager;
    NotificationReciever* reciever;
    CommandDispatcher* dispatcher;

    GtkWidget *window_connect;
    GtkWidget *window_login;

    bool OK;

    ClientSocket* sock;

    GtkEntry *entry_ip;
    GtkEntry *entry_port;
    GtkEntry *entry_name;

    void Run(int* argc, char***argv);
};


#endif //TOWERDEFENSE_GTKRUNNER_H
