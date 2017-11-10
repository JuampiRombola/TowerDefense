#ifndef TOWERDEFENSE_SDLRUNNER_H
#define TOWERDEFENSE_SDLRUNNER_H

#include <thread>
#include "View/Common/Window.h"
#include "View/Common/Renderer.h"
#include "View/Common/TextureLoader.h"
#include "View/Model/MapView.h"
#include "View/Common/SpriteNamesConfig.h"
#include "View/Model/PortalEntradaView.h"
#include "View/Model/PortalSalidaView.h"
#include "View/Model/TowerView.h"
#include "View/Model/UnitView.h"
#include "TowerDefenseServer/include/GameConfiguration.h"
#include "TowerDefenseServer/include/TowerDefenseGame.h"
#include "TowerDefenseServer/include/ThreadSafeQueue.h"
#include "TowerDefenseServer/include/GameNotifications/GameNotification.h"
#include "TowerDefenseServer/include/Commands/BuildTowerCommand.h"


#define TITLE "Tower Defense"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 7

class SDLRunner {
public:
    SDLRunner();
    ~SDLRunner();
    void Run();
};


#endif