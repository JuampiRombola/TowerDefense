#include "../../include/GTKNotifications/LeftLobbyGTKNotification.h"
#include "../../GTKRunner.h"


LeftLobbyGTKNotification::LeftLobbyGTKNotification() {
	
}

LeftLobbyGTKNotification::~LeftLobbyGTKNotification(){
	
}

void LeftLobbyGTKNotification::Execute(GTKRunner& runner){
    g_object_ref(runner.grid_lobby);
    gtk_container_remove(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobby));
    gtk_container_add(GTK_CONTAINER(runner.box1), GTK_WIDGET(runner.grid_lobbies));
}