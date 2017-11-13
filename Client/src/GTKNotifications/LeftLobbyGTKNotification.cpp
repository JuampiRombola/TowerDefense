#include "../../include/GTKNotifications/LeftLobbyGTKNotification.h"
#include "../../GTKRunner.h"


LeftLobbyGTKNotification::LeftLobbyGTKNotification() {
	
}

LeftLobbyGTKNotification::~LeftLobbyGTKNotification(){
	
}

void LeftLobbyGTKNotification::Execute(GTKRunner& runner){
    gtk_widget_show (GTK_WIDGET(runner.window_lobbies));
}