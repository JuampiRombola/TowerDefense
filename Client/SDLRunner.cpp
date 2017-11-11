#include "SDLRunner.h"
SDLRunner::SDLRunner() {

}
SDLRunner::~SDLRunner() {

}

void SDLRunner::Run(){
    //std::string ss("../TowerDefenseServer/config.yaml");
    //GameConfiguration cfg(ss);
    //uint clockDelaymilliseconds = 100;
    //ThreadSafeQueue<GameNotification*> notis;
    //TowerDefenseGame game(clockDelaymilliseconds, cfg, notis);
    //std::thread gameClock(&TowerDefenseGame::Run, &game);

    //BuildTowerCommand tower(Ground, 2, 5);
    //game.QueueCommand(&tower);

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
                            /* case SDLK_d:
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
                                 unit.move(0, 0, 1, 0, 3000);; break;*/
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


        /*
        GameNotification *noti = notis.Dequeue();
        while (noti != nullptr) {
            noti->NotifyUnits(units, textureLoader, renderer);
            noti->NotifyShots(shots, textureLoader, renderer);
            noti = notis.Dequeue();
        }

        for (auto it = units.begin(); it != units.end(); ++it) {
            ticks = SDL_GetTicks();
            (*it)->draw(ticks);
        }

        for (auto it = shots.begin(); it != shots.end(); ++it) {
            (*it)->draw(ticks);
        }*/

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
}
