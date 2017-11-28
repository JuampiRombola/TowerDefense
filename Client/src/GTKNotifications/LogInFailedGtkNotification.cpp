//
// Created by tino on 11/11/17.
//

#include <gtkmm/messagedialog.h>
#include "../../include/GTKNotifications/LogInFailedGtkNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

LogInFailedGtkNotification::LogInFailedGtkNotification(){

}

LogInFailedGtkNotification::~LogInFailedGtkNotification(){

}

void LogInFailedGtkNotification::Execute(GTKmmRunner& runner){

    Gtk::MessageDialog dialog("Name already taken!", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text( "Pick another one..." );
    dialog.run();
}