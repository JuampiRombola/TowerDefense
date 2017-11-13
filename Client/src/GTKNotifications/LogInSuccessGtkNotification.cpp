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

    gtk_widget_hide (GTK_WIDGET(runner.window_login));
    gtk_widget_show (GTK_WIDGET(runner.window_lobbies));
}