//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_GTKMMRUNNER_H
#define TOWERDEFENSE_GTKMMRUNNER_H


#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "FixedConnect.h"
#include "FixedLogin.h"
#include "FixedLobbies.h"
#include "FixedLobby.h"
#include "../include/ClientSocket.h"
#include "../include/Lobbies/ClientLobbyManager.h"
#include "../include/NotificationReciever.h"

class GTKmmRunner {

private:


public:
    GTKmmRunner();
    ~GTKmmRunner();

    void Run(int* argc, char***argv);

    Gtk::Window* window_global;


    void connect_clicked();
    void login_clicked();
    void newlobby_clicked();
    void joinlobby_clicked();
    void leavelobby_clicked();
    void lobbyready_clicked();
    void map_changed();

    void radio_fire_clicked();
    void radio_water_clicked();
    void radio_ground_clicked();
    void radio_air_clicked();


    static gboolean notification_check(gpointer data);

    void ShutDown();
    Gtk::Box* box;

    FixedConnect fixed_connect;
    FixedLogin fixed_login;
    FixedLobbies fixed_lobbies;
    FixedLobby fixed_lobby;


    ClientSocket* sock;
    ClientLobbyManager* lobbyManager;
    NotificationReciever* reciever;
    CommandDispatcher* dispatcher;

    NonBlockingThreadSafeQueue<GTKNotification*> gtkNotifications;

    uint8_t MapSurface;
    uint32_t MapWidth;
    uint32_t MapHeight;
    bool OK;

};


#endif //TOWERDEFENSE_GTKMMRUNNER_H
