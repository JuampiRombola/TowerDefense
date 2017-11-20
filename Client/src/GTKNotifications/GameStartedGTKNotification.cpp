#include <gtk/gtk.h>
#include "../../include/GTKNotifications/GameStartedGTKNotification.h"
#include "../../GTKRunner.h"


GameStartedGTKNotification::GameStartedGTKNotification(uint8_t sup, uint32_t width, uint32_t height)
: _sup(sup), _width(width), _height(height)
{

}

GameStartedGTKNotification::~GameStartedGTKNotification(){
	
}

void GameStartedGTKNotification::Execute(GTKRunner& runner){
    GTKRunner::ShutdownGTK();
    runner.OK = true;
    runner.MapSurface = _sup;
    runner.MapWidth = _width;
    runner.MapHeight = _height;
}