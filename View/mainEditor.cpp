#include <iostream>
#include "Common/Window.h"
#include "Common/Renderer.h"
#include "Common/TextureLoader.h"
#include "Model/MapView.h"
#include "Common/MousePosition.h"
#include "Editor/Editor.h"
#include "Common/KeyboardInput.h"
#include "Editor/Buttons.h"

#define TITLE "Tower Defense"
#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

#define MAPSIZE 10

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer());

    MapView mapView(MAPSIZE, MAPSIZE, PRADERA, renderer, textureLoader);

    int mouse_x = -1, mouse_y = -1;
    MousePosition mouse(mouse_x, mouse_y);

    Editor editor;

    KeyboardInput keyboardInput(editor.getNombre());

    Buttons buttons(mouse, renderer, editor, textureLoader, keyboardInput);
    buttons.addSuperficieButtons();
    buttons.addNuevaHordaButton();

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
            case SDL_FINGERDOWN:
                mouse_x = static_cast<int>(event.tfinger.x);
                mouse_y = static_cast<int>(event.tfinger.y);
                mouse.toggleActive();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_PLUS: renderer.zoomIn(); break;
                    case SDLK_MINUS: renderer.zoomOut(); break;
                    case SDLK_LEFT:  renderer.updateCamera(-1, 0); break;
                    case SDLK_RIGHT: renderer.updateCamera(1, 0); break;
                    case SDLK_UP:    renderer.updateCamera(0, -1); break;
                    case SDLK_DOWN:  renderer.updateCamera(0, 1); break;
                }
        }
        event.type = 0;
        renderer.clearRender();
        buttons.cleanHordasButtons();
        for (unsigned int horda = 0; horda < editor.getCantidadHordas();
             ++horda) {
            buttons.addEnemigosButton(horda);
        }
        mapView.draw(0);
        buttons.draw();
        renderer.present();
    }
    editor.exportar();
    SDL_Quit();
    return 0;
}

