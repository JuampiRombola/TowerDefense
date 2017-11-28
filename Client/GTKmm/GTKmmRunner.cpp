//
// Created by tino on 27/11/17.
//

#include <gtkmm/application.h>
#include <gtkmm/messagedialog.h>
#include "GTKmmRunner.h"
#include "../include/NetCommands/LogInCommand.h"
#include "../include/NetCommands/CreateLobbyCommand.h"
#include "../include/NetCommands/JoinLobbyCommand.h"
#include "../include/NetCommands/PickSpellCommand.h"
#include "../include/NetCommands/LeaveLobbyCommand.h"
#include "../include/NetCommands/PickMapCommand.h"
#include "../include/NetCommands/PlayerIsReadyCommand.h"
#include "../../Common/Paths.h"


GTKmmRunner::GTKmmRunner() : OK(false) {

}

GTKmmRunner::~GTKmmRunner() {

}

void GTKmmRunner:: ConnectionLost(){
    Gtk::MessageDialog dialog("Server went down!", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text( "Try again later..." );
    dialog.run();
    ShutDown();
}


void GTKmmRunner::Run(int* argc, char***argv){

    auto app = Gtk::Application::create(*argc, *argv);
    auto refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file(PATH_CONFIG + std::string("") + "Client/Launchermm.glade");
    refBuilder->get_widget("window_global", window_global);
    refBuilder->get_widget("box", box);

    fixed_connect.Set(refBuilder);
    fixed_login.Set(refBuilder);
    fixed_lobby.Set(refBuilder);
    fixed_lobbies.Set(refBuilder);

    box->remove(*(fixed_login.fixed));
    box->remove(*(fixed_lobby.fixed));
    box->remove(*(fixed_lobbies.fixed));

    fixed_connect.button_connect->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::connect_clicked));
    fixed_login.button_login->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::login_clicked));
    fixed_lobbies.button_newLobby->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::newlobby_clicked));
    fixed_lobbies.button_joinLobby->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::joinlobby_clicked));
    fixed_lobby.button_leave->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::leavelobby_clicked));
    fixed_lobby.button_ready->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::lobbyready_clicked));
    
    
    fixed_lobby.toggle_air->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::radio_air_clicked));
    fixed_lobby.toggle_fire->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::radio_fire_clicked));
    fixed_lobby.toggle_water->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::radio_water_clicked));
    fixed_lobby.toggle_ground->signal_clicked().connect(sigc::mem_fun(this, &GTKmmRunner::radio_ground_clicked));
    fixed_lobby.combobox_changed_signal = fixed_lobby.combobox_maps->signal_changed().connect(sigc::mem_fun(this, &GTKmmRunner::map_changed));

    window_global->set_default_size(960, 540);
    window_global->show_all();
    app->run(*window_global);
}


gboolean GTKmmRunner::notification_check(gpointer data){
    GTKmmRunner* runner = (GTKmmRunner*) data;
    GTKNotification* gtkNoti = runner->gtkNotifications.Dequeue();
    while (gtkNoti != nullptr){
        gtkNoti->Execute(*runner);
        delete gtkNoti;
        gtkNoti = runner->gtkNotifications.Dequeue();
    }
    return false;
}

void GTKmmRunner::ShutDown(){
    window_global->close();
}

void GTKmmRunner::login_clicked() {
    Glib::ustring name = fixed_login.entry_name->get_text();
    if (name.size() > 0)
        dispatcher->QueueCommand(new LogInCommand(name));
}

void GTKmmRunner::newlobby_clicked(){
    Glib::ustring lobbyname = fixed_lobbies.entry_newLobbyName->get_text();
    if (lobbyname.size() > 0)
        dispatcher->QueueCommand(new CreateLobbyCommand(lobbyname));
}

void GTKmmRunner::joinlobby_clicked(){
    int id = fixed_lobbies.GetSelectedLobbyId();
    if (id > 0)
        dispatcher->QueueCommand(new JoinLobbyCommand(id));
}

void GTKmmRunner::leavelobby_clicked(){
   dispatcher->QueueCommand(new LeaveLobbyCommand());
}

void GTKmmRunner::lobbyready_clicked(){
    dispatcher->QueueCommand(new PlayerIsReadyCommand());
}

void GTKmmRunner::radio_fire_clicked(){
    if (fixed_lobby.toggle_fire->get_state_flags() == Gtk::StateFlags::STATE_FLAG_CHECKED)
        return;
    dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_FIRE));
}

void GTKmmRunner::radio_water_clicked(){
    if (fixed_lobby.toggle_water->get_state_flags() == Gtk::StateFlags::STATE_FLAG_CHECKED)
        return;
    dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_WATER));
}

void GTKmmRunner::radio_ground_clicked(){
    if (fixed_lobby.toggle_ground->get_state_flags() == Gtk::StateFlags::STATE_FLAG_CHECKED)
        return;
    dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_GROUND));
}

void GTKmmRunner::map_changed(){
    auto row = *(fixed_lobby.combobox_maps->get_active());
    if (row){
        uint i = row->get_value(fixed_lobby.columns_maps.m_col_map_id);
        fixed_lobby.combobox_changed_signal.block();
        fixed_lobby.combobox_maps->set_active(-1);
        fixed_lobby.combobox_changed_signal.unblock();
        dispatcher->QueueCommand(new PickMapCommand(i));
    }
}

void GTKmmRunner::radio_air_clicked(){
    if (fixed_lobby.toggle_air->get_state_flags() == Gtk::StateFlags::STATE_FLAG_CHECKED)
        return;
    dispatcher->QueueCommand(new PickSpellCommand(SPELL_TYPE_AIR));
}






void GTKmmRunner::connect_clicked(){
    Glib::ustring port = fixed_connect.entry_port->get_text();
    Glib::ustring ip = fixed_connect.entry_ip->get_text();
    sock = new ClientSocket(ip, port);
    if (sock->Connected()){
        lobbyManager = new ClientLobbyManager(*sock, *this);
        dispatcher = new CommandDispatcher(*sock);
        reciever = new NotificationReciever(*sock, *lobbyManager, *this, *dispatcher);
        dispatcher->Run();
        reciever->Run();

        box->remove(*fixed_connect.fixed);
        box->add(*fixed_login.fixed);
        // g_object_ref(grid_connect);
        // gtk_container_remove(GTK_CONTAINER(runner->box1), GTK_WIDGET(runner->grid_connect));
        // gtk_container_add(GTK_CONTAINER(runner->box1), GTK_WIDGET(runner->grid_login));
    }
    else
    {
        Gtk::MessageDialog dialog("Connection error!", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text( "Try again..." );
        dialog.run();
    }
}