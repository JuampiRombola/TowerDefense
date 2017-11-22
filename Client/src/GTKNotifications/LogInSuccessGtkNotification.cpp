//
// Created by tino on 11/11/17.
//

#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../GTKRunner.h"
#include <gtk/gtk.h>



LogInSuccessGtkNotification::LogInSuccessGtkNotification(std::vector<Lobby*>& lobbies) : _lobbies(lobbies){

}

LogInSuccessGtkNotification::~LogInSuccessGtkNotification(){

}

void LogInSuccessGtkNotification::Execute(GTKRunner& runner){

    g_object_ref(runner.grid_login);
    gtk_container_remove(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_login));
    gtk_container_add(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobbies));

    //gtk_widget_hide (GTK_WIDGET(runner.window_login));
    //gtk_widget_show (GTK_WIDGET(runner.window_lobbies));
}