#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "MapView.h"
#include "../src/PathTile.h"
#include "../src/SolidGroundTile.h"

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 10
#define ENVPRADERA 0

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(&window, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer());

    std::vector<PathTile*> pathTiles;
    std::vector<SolidGroundTile*> structureTiles;

    MapView mapView(MAPSIZE, MAPSIZE, ENVPRADERA, &renderer,
                    &pathTiles, &structureTiles,&textureLoader);

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                std::cout << "Estoy haciendo click" << "\n";
                int x, y;
                SDL_GetMouseState(&x, &y);
                std::cout << "Hice click en (" << x << "," << y << ")\n";
                break;
        }
        renderer.clearRender();
        Uint32 ticks = SDL_GetTicks();
        mapView.draw(ticks);
        renderer.present();
    }
    SDL_Quit();
}