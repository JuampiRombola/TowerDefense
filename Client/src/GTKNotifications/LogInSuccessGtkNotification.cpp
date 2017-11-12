//
// Created by tino on 11/11/17.
//

#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../GTKRunner.h"
#include "../../include/NetCommands/GetLobbiesCommand.h"
#include <gtk/gtk.h>



LogInSuccessGtkNotification::LogInSuccessGtkNotification(){

}

LogInSuccessGtkNotification::~LogInSuccessGtkNotification(){

}

void LogInSuccessGtkNotification::Execute(GTKRunner& runner){
    gtk_widget_hide (GTK_WIDGET(runner.window_login));
    gtk_widget_show (GTK_WIDGET(runner.window_lobbies));
    runner.dispatcher->QueueCommand(new GetLobbiesCommand());
}