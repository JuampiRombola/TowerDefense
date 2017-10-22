#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "MapView.h"
<<<<<<< HEAD
#include "SpriteNamesConfig.h"
=======
#include "../src/PathTile.h"
#include "../src/SolidGroundTile.h"
>>>>>>> a6e3d36613f80f66fc031a8349f388a120cee68a

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 7

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer());

<<<<<<< HEAD
    MapView mapView(MAPSIZE, MAPSIZE, PRADERA, renderer, textureLoader);
=======
    std::vector<PathTile*> pathTiles;
    std::vector<SolidGroundTile*> structureTiles;
>>>>>>> a6e3d36613f80f66fc031a8349f388a120cee68a

    //Armo un camino
    mapView.addPathTile(0, 0);
    mapView.addPathTile(1, 0);
    mapView.addPathTile(1, 1);
    mapView.addPathTile(1, 2);
    mapView.addPathTile(1, 3);
    mapView.addPathTile(2, 3);
    mapView.addPathTile(3, 3);
    mapView.addPathTile(3, 4);
    mapView.addPathTile(3, 5);
    mapView.addPathTile(4, 5);
    mapView.addPathTile(5, 5);
    mapView.addPathTile(6, 5);
    mapView.addPathTile(6, 6);

    //Pongo tierra firme
    mapView.addStructureTile(0, 1);
    mapView.addStructureTile(2, 2);
    mapView.addStructureTile(3, 2);
    mapView.addStructureTile(4, 4);
    mapView.addStructureTile(5, 6);

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
<<<<<<< HEAD
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
=======
            case SDL_MOUSEBUTTONUP:
                std::cout << "Estoy haciendo click" << "\n";
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::cout << "Hice click en (" << x << "," << y << ")\n";
                break;
>>>>>>> a6e3d36613f80f66fc031a8349f388a120cee68a
        }
        renderer.clearRender();
        Uint32 ticks = SDL_GetTicks();
        mapView.draw(ticks);
        renderer.present();
    }
    SDL_Quit();
}