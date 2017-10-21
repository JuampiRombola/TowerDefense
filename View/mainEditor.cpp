#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "MapView.h"
#include "MousePosition.h"
#include "../src/PathTile.h"
#include "../src/SolidGroundTile.h"
#include "Buttons.h"
#include "Editor.h"

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

    int mouse_x = -1, mouse_y = -1;
    MousePosition mouse(mouse_x, mouse_y);

    Editor editor;

    Buttons buttons(mouse, renderer, editor);
    buttons.addSuperficieButtons(textureLoader.getTexture(9), textureLoader
            .getTexture(6), textureLoader.getTexture(7), textureLoader
            .getTexture(8));

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                mouse.toggleActive();
                break;
        }
        event.type = 0;
        renderer.clearRender();
        buttons.draw();
        renderer.present();
    }
    SDL_Quit();
    return 0;
}

