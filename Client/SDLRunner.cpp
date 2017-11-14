#include "SDLRunner.h"
#include "include/NetCommands/CommandDispatcher.h"
#include "include/NotificationReciever.h"
#include "include/ClientSocket.h"
#include "View/Model/ModelView.h"
#include "View/Model/ViewConstants.h"
#include "View/Model/HudView.h"

#define TITLE "Tower Defense"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480
#define FPS 40

#define MAPSIZE 7

SDLRunner::SDLRunner() {

}
SDLRunner::~SDLRunner() {
    delete _dispatcher;
    delete _reciever;
    delete _lobbyManager;
    std::cout << "lobbymanager deleted\n" << std::flush;
    delete _sock;
    std::cout << "sock deleted\n" << std::flush;
}

void SDLRunner::Run(CommandDispatcher* dispatcher, NotificationReciever* reciever, ClientLobbyManager* lobbyManager, ClientSocket* sock)
{
    bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), 0);

    _dispatcher = dispatcher;
    _lobbyManager = lobbyManager;
    _reciever = reciever;
    _sock = sock;
    
    ModelView* mv = new ModelView(renderer, textureLoader);
    _reciever->model_view =  mv;

    mv->setMapEnvironment(DESIERTO);
    mv->setMapWidthHeight(MAPSIZE, MAPSIZE);
    
    mv->createPathTile(0, 0);
    mv->createPathTile(1, 0);
    mv->createPathTile(1, 1);
    mv->createPathTile(2, 1);
    mv->createPathTile(3, 1);
    mv->createPathTile(3, 2);
    mv->createPathTile(3, 3);
    mv->createPathTile(2, 3);
    mv->createPathTile(2, 4);
    mv->createPathTile(2, 5);
    mv->createPathTile(3, 5);
    mv->createPathTile(4, 5);
    mv->createPathTile(5, 5);
    mv->createPathTile(6, 5);
    mv->createPathTile(6, 6);

    mv->createStructureTile(1, 4);
    mv->createStructureTile(2, 0);
    mv->createStructureTile(2, 2);
    mv->createStructureTile(3, 4);
    mv->createStructureTile(4, 6);

    mv->createPortalEntrada(0, 0);
    mv->createPortalSalida(6, 6);

    /*mv->createTower(1, TORRE_TIERRA, 2, 0);
    mv->createTower(2, TORRE_AIRE, 2, 2);
    mv->createTower(3, TORRE_FUEGO, 1, 4);
    mv->createTower(4, TORRE_AGUA, 4, 6);*/
    HudView hudView(window, textureLoader, renderer, *_dispatcher);
    hudView.addElementalButtons(ELEMENTAL_EARTH);
    hudView.addElementalButtons(ELEMENTAL_FIRE);
    hudView.addElementalButtons(ELEMENTAL_WATER);
    hudView.addElementalButtons(ELEMENTAL_AIR);

    Uint32 t1;
    Uint32 t2;
    Uint32 s = 1000 / FPS;
    Uint32 delta = 0;
    Uint32 elapsedTime = 0;
    Uint32 delayTime = 0;

    int idUnit = 0;
    while (!quit && _reciever->Running()) {
        t1 = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true; break;
                case SDL_MOUSEBUTTONDOWN:
                    hudView.getMouseState();
                    break;
                case SDL_FINGERDOWN:
                    hudView.getFingerState(event);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true; break;
                        case SDLK_i:
                            renderer.zoomIn(); break;
                        case SDLK_o:
                            renderer.zoomOut(); break;
                        case SDLK_LEFT:
                            renderer.updateCamera(-1, 0); break;
                        case SDLK_RIGHT:
                            renderer.updateCamera(1, 0); break;
                        case SDLK_UP:
                            renderer.updateCamera(0, -1); break;
                        case SDLK_DOWN:
                            renderer.updateCamera(0, 1); break;
                    }
            }
            hudView.doMouseAction();
        }
        renderer.clearRender();
        mv->draw(SDL_GetTicks());
        hudView.draw();
        renderer.present();
        t2 = SDL_GetTicks();
        elapsedTime = t2 - t1 + delta;
        delayTime = s - elapsedTime;
        if (elapsedTime < s) {
            SDL_Delay(delayTime);
            delta = SDL_GetTicks() - t2 - delayTime;
        } else
            delta = elapsedTime - s;
    }
    SDL_Quit();

    delete mv;
}


/*
 * 
 * 
 * 
 * 
 * 

                        case SDLK_d:
                            mv->killUnit(1); break;
                            //unit.enableDying(); break;
                        case SDLK_s:
                            mv->createShot(DISPARO_TIERRA, 2, 0, 0, 0, 500);break;
                            //shot.shoot(2, 0, 0, 0, 500); break;
                        case SDLK_a:
                            mv->createSpell(FIREWALL, 1, 1, 5000);break;
                            //fireWall.cast(1, 1, 5000); break;
                        case SDLK_q:
                            mv->createUnit(++idUnit, ABOMINABLE, 0, 0, 1, 0, 3000); break;
                        case SDLK_z:
                            mv->moveUnit(1, 1, 0, 1, 1, 3000);break;
                            //unit.move(1, 0, 1, 1, 3000); break;
                        case SDLK_x:
                            mv->moveUnit(1, 1, 1, 2, 1, 3000);break;
                            //unit.move(1, 1, 0, 1, 3000); break;
                        case SDLK_c:
                            mv->moveUnit(1, 2, 1, 3, 1, 3000);break;
                            //unit.move(0, 1, 0, 0, 3000); break;
                        case SDLK_v:
                            mv->moveUnit(1, 3, 1, 3, 2, 3000);break;
                            //unit.move(0, 0, 1, 0, 3000); break;
                        case SDLK_b:
                            mv->moveUnit(1, 3, 2, 3, 3, 3000);break;
                        case SDLK_n:
                            mv->moveUnit(1, 3, 3, 2, 3, 3000);break;
                        case SDLK_m:
                            mv->moveUnit(1, 2, 3, 2, 4, 3000);break;
                            
                            
  bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), 0);

    MapView mapView(MAPSIZE, MAPSIZE, PRADERA, renderer, textureLoader);

    //Armo un camino
    mapView.addPathTile(0, 0);
    mapView.addPathTile(1, 0);
    mapView.addPathTile(1, 1);
    mapView.addPathTile(1, 2);
    mapView.addPathTile(1, 3);
    mapView.addPathTile(2, 3);
    mapView.addPathTile(2, 4);
    mapView.addPathTile(3, 4);
    mapView.addPathTile(3, 5);
    mapView.addPathTile(4, 5);
    mapView.addPathTile(5, 5);
    mapView.addPathTile(6, 5);
    mapView.addPathTile(6, 6);

    //Pongo tierra firme
    mapView.addStructureTile(1, 4);
    mapView.addStructureTile(2, 5);
    mapView.addStructureTile(4, 4);
    mapView.addStructureTile(5, 6);

    //Pongo un portal de entrada y uno de salida
    PortalEntradaView portalEntrada = PortalEntradaView(textureLoader, renderer);
    portalEntrada.setXY(0, 0);
    PortalSalidaView portalSalida = PortalSalidaView(textureLoader, renderer);
    portalSalida.setXY(6, 6);

    //Agrego una torre de fuego en el 1,4
    TowerView groundTower(1, TORRE_TIERRA, textureLoader, renderer);
    groundTower.setXY(2, 5);

    //Agrego una torre de fuego en el 4,4
//    TowerView fireTower2(2, TORRE_FUEGO, textureLoader, renderer);
//    fireTower2.setXY(4, 4);

    //Creo una unidad en el 0,0
    //UnitView unit(1, ABOMINABLE, textureLoader, renderer);
    //unit.move(0, 0, 1, 0, 5000);

    //std::vector<UnitView*> units;
    //std::vector<ShotView*> shots;



    uint32_t  fps = 40;
    Uint32 t1;
    Uint32 t2;
    Uint32 s = 1000 / fps;
    Uint32 delta = 0;
    Uint32 elapsedTime = 0;
    Uint32 delayTime = 0;

    while (!quit) {
        t1 = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_i:
                            renderer.zoomIn();
                            break;
                        case SDLK_o:
                            renderer.zoomOut();
                            break;
                             case SDLK_d:
                                 unit.enableDying(); break;
                             case SDLK_s:
                                 shot.shoot(2, 0, 0, 0, 500); break;
                             case SDLK_a:
                                 fireWall.cast(1, 1, 5000); break;
                             case SDLK_z:
                                 unit.move(1, 0, 1, 1, 3000);; break;
                             case SDLK_x:
                                 unit.move(1, 1, 0, 1, 3000);; break;
                             case SDLK_c:
                                 unit.move(0, 1, 0, 0, 3000);; break;
                             case SDLK_v:
                                 unit.move(0, 0, 1, 0, 3000);; break;
case SDLK_LEFT:
        renderer.updateCamera(-1, 0);
break;
case SDLK_RIGHT:
        renderer.updateCamera(1, 0);
break;
case SDLK_UP:
        renderer.updateCamera(0, -1);
break;
case SDLK_DOWN:
        renderer.updateCamera(0, 1);
break;
}
}
}
renderer.clearRender();

Uint32 ticks = SDL_GetTicks();
mapView.draw(ticks);
portalEntrada.draw(ticks);
portalSalida.draw(ticks);



SDLNotification *noti = _sdlNotifications.Dequeue();
while (noti != nullptr) {
noti->Execute();
noti = notis.Dequeue();
}

for (auto it = units.begin(); it != units.end(); ++it) {
ticks = SDL_GetTicks();
(*it)->draw(ticks);
}

for (auto it = shots.begin(); it != shots.end(); ++it) {
(*it)->draw(ticks);
}

groundTower.draw(ticks);

renderer.present();

t2 = SDL_GetTicks();
elapsedTime = t2 - t1 + delta;
delayTime = s - elapsedTime;
if (elapsedTime < s) {
SDL_Delay(delayTime);
delta = SDL_GetTicks() - t2 - delayTime;
} else
delta = elapsedTime - s;
}
SDL_Quit();
 */