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
    COLUMN_LOBBY_NAME,
    COLUMN_LOBBY_ID,
    LOBBIES_N_COLUMNS
};

enum LobbyPlayersListEnum {
    COLUMN_PLAYER_NAME,
    COLUMN_PLAYER_READY,
    LOBBY_PLAYERS_N_COLUMNS
};

class GTKRunner {
private:
    static void _ShutdownGTK();
    static void _LobbyWindowClosed();
    static void newLobby_clicked(GtkWidget* widget, gpointer data);
    static void joinLobby_clicked(GtkWidget* widget, gpointer data);
    static void connect_clicked(GtkWidget* widget, gpointer data);
    static void login_clicked(GtkWidget* widget, gpointer data);
    static void leaveLobby_clicked(GtkWidget* widget, gpointer data);
    static void lobbyReady_clicked(GtkWidget* widget, gpointer data);
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
    GtkWindow *window_lobby;


    void InitLobbyPlayersTreeView();
    void InitLobbiesTreeView();

    GtkTreeView *treeview_lobbies;
    GtkTreeView *treeview_lobbyPlayers;

    GtkLabel* label_lobbyname;

    bool OK;
    void MessageBox(std::string s);

    ClientSocket* sock;

    GtkEntry *entry_ip;
    GtkEntry *entry_port;
    GtkEntry *entry_name;
    GtkEntry *entry_newLobbyName;

    void Run(int* argc, char***argv);
};



#endif //TOWERDEFENSE_GTKRUNNER_H