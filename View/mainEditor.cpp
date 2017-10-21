#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "MapView.h"
#include "MousePosition.h"
#include "../src/PathTile.h"
#include "../src/SolidGroundTile.h"

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 10
#define ENVPRADERA 0

int mainEditor(int argc, char** argv) {
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(&window, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer());

    std::vector<PathTile *> pathTiles;
    std::vector<SolidGroundTile *> structureTiles;


    MapView mapView(MAPSIZE, MAPSIZE, ENVPRADERA, &renderer, &pathTiles,
                    &structureTiles, &textureLoader);

    int mouse_x = 0, mouse_y = 0;
    bool clicked = false;
    MousePosition mouse(mouse_x, mouse_y, clicked);

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << "Estoy haciendo click" << "\n";
                SDL_GetMouseState(&mouse_x, &mouse_y);
                clicked = true;
                break;
            case SDL_MOUSEBUTTONUP:
                std::cout << "Solté el click" << "\n";
                clicked = false;
                break;
        }
        event.type = 0;
        renderer.clearRender();
        Uint32 ticks = SDL_GetTicks();
        mapView.draw(ticks);
        renderer.present();
    }
    SDL_Quit();
    return 0;
}

