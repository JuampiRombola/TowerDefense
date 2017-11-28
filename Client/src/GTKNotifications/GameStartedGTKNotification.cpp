#include "../../include/GTKNotifications/GameStartedGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


GameStartedGTKNotification::GameStartedGTKNotification(uint8_t sup, uint32_t width, uint32_t height)
: _sup(sup), _width(width), _height(height)
{

}

GameStartedGTKNotification::~GameStartedGTKNotification(){
	
}

void GameStartedGTKNotification::Execute(GTKmmRunner& runner){
    //GTKmmRunner::ShutdownGTK();
    runner.window_global->close();
    runner.OK = true;
    runner.MapSurface = _sup;
    runner.MapWidth = _width;
    runner.MapHeight = _height;
}