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
#include "include/NonBlockingThreadSafeQueue.h"
#include "include/GTKNotifications/GTKNotification.h"
#include "include/SDLNotifications/SDLNotification.h"


enum LobbiesListEnum {
    COLUMN_STRING,
    COLUMN_INT,
    COLUMN_BOOLEAN,
    N_COLUMNS
};

class GTKRunner {
private:
    static void ShutdownGTK();
    static void newLobby_clicked(GtkWidget* widget, gpointer data);
    static void joinLobby_clicked(GtkWidget* widget, gpointer data);
    static void connect_clicked(GtkWidget* widget, gpointer data);
    static void login_clicked(GtkWidget* widget, gpointer data);
public:
    GTKRunner();
    ~GTKRunner();

    NonBlockingThreadSafeQueue<GTKNotification*> gtkNotifications;
    ClientLobbyManager* lobbyManager;
    NotificationReciever* reciever;
    CommandDispatcher* dispatcher;

    GtkWindow *window_connect;
    GtkWindow *window_login;
    GtkWindow *window_lobbies;

    GtkListBox *listbox_lobbies;
    GtkListStore *list_store_lobbies;

    bool OK;
    void MessageBox(std::string s);

    void LogInSuccess();
    void LogInFailed();

    ClientSocket* sock;

    GtkEntry *entry_ip;
    GtkEntry *entry_port;
    GtkEntry *entry_name;
    GtkEntry *entry_newLobbyName;

    void Run(int* argc, char***argv);
};



#endif //TOWERDEFENSE_GTKRUNNER_H
