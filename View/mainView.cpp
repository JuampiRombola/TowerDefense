#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "MapView.h"
#include "SpriteNamesConfig.h"
#include "PortalEntradaView.h"
#include "PortalSalidaView.h"
#include "FireTowerView.h"

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 10

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer());

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
    FireTowerView fireTower1(textureLoader, renderer);
    fireTower1.setXY(1, 4);

    //Agrego una torre de fuego en el 4,4
    FireTowerView fireTower2(textureLoader, renderer);
    fireTower2.setXY(4, 4);

    while (!quit) {
        //t1
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_i: renderer.zoomIn(); break;
                    case SDLK_o: renderer.zoomOut(); break;
                    case SDLK_LEFT:  renderer.updateCamera(-1, 0); break;
                    case SDLK_RIGHT: renderer.updateCamera(1, 0); break;
                    case SDLK_UP:    renderer.updateCamera(0, -1); break;
                    case SDLK_DOWN:  renderer.updateCamera(0, 1); break;
                }
        }
        renderer.clearRender();
        Uint32 ticks = SDL_GetTicks();
        mapView.draw(ticks);
        portalEntrada.draw(ticks);
        portalSalida.draw(ticks);
        fireTower1.draw(ticks);
        fireTower2.draw(ticks);
        renderer.present();// t2
        //delay(S - t2 + t1 - d)
        //t3
        //d = t2 - t3 - (S - t2 + t1)
    }
    SDL_Quit();
}