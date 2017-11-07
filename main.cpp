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

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 7

int main(int argc, char** argv) {

    std::string ss("../TowerDefenseServer/config.yaml");
    GameConfiguration cfg(ss);
    uint clockDelaymilliseconds = 100;
    TowerDefenseGame game(clockDelaymilliseconds, cfg);
    std::thread gameClock(&TowerDefenseGame::Run, &game);


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
    mapView.addStructureTile(2, 2);
    mapView.addStructureTile(4, 4);
    mapView.addStructureTile(5, 6);

    //Pongo un portal de entrada y uno de salida
    PortalView portalEntrada = PortalEntradaView(textureLoader, renderer);
    portalEntrada.setXY(0, 0);
    PortalView portalSalida = PortalSalidaView(textureLoader, renderer);
    portalSalida.setXY(6, 6);

    //Agrego una torre de fuego en el 1,4
    TowerView fireTower1(TORRE_FUEGO, textureLoader, renderer);
    fireTower1.setXY(1, 4);

    //Agrego una torre de fuego en el 4,4
    TowerView fireTower2(TORRE_FUEGO, textureLoader, renderer);
    fireTower2.setXY(4, 4);

    //Creo una unidad en el 0,0
    UnitView unit(ABOMINABLE, textureLoader, renderer);
    unit.move(0, 0, 1, 0, 5000);

    Uint32 t1;
    Uint32 t2;
    Uint32 s = 1000 / 30;
    Uint32 delta = 0;
    Uint32 elapsedTime = 0;
    Uint32 delayTime = 0;

    while (!quit) {
        t1 = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true; break;
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
        }
        renderer.clearRender();

        Uint32 ticks = SDL_GetTicks();
        mapView.draw(ticks);
        portalEntrada.draw(ticks);
        portalSalida.draw(ticks);


        std::vector<UnitVM> unitVms = game.GetUnitViewModels();
        if (unitVms.begin() != unitVms.end()){
            UnitVM vm = *unitVms.begin();
            unit.move(vm.xPos, vm.yPos, 0, 0, 5000);
        }
        

        unit.draw(ticks);
        fireTower1.draw(ticks);
        fireTower2.draw(ticks);

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

    gameClock.join();
    SDL_Quit();
}