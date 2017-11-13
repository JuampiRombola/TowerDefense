#include <gtk/gtk.h>
#include "../../include/GTKNotifications/GameStartedGTKNotification.h"
#include "../../GTKRunner.h"


GameStartedGTKNotification::GameStartedGTKNotification()
{

}

GameStartedGTKNotification::~GameStartedGTKNotification(){
	
}

void GameStartedGTKNotification::Execute(GTKRunner& runner){
    GTKRunner::ShutdownGTK();
    runner.OK = true;
}