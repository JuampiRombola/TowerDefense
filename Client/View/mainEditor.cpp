#include <iostream>
#include "Common/Window.h"
#include "Common/Renderer.h"
#include "Common/TextureLoader.h"
#include "Model/MapView.h"
#include "Common/MousePosition.h"
#include "Editor/Editor.h"
#include "Editor/EditorButtons.h"
#include "Common/MusicLoader.h"
#include "Common/MouseMovement.h"

#define TITLE "Tower Defense"
#define CONFIG_PATH "/etc/TowerDefense/windowConfig.yaml"
#define EDITOR_MODE 1
#define SALIDA_DEFAULT "mapa"

#define MAPSIZE 7

int main(int argc, char **argv) {
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    YAML::Node windowConfig(YAML::LoadFile(CONFIG_PATH));
    Window window(TITLE, windowConfig["editor_width"].as<int>(),
                  windowConfig["editor_height"].as<int>(),
                  windowConfig["editor_fullscreen"].as<bool>() ? SDL_WINDOW_FULLSCREEN_DESKTOP
                                                               : SDL_WINDOW_FOREIGN);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), EDITOR_MODE);
    MouseMovement mouseMovement(renderer);
    MusicLoader musicLoader;
    musicLoader.playMusic();
    MapView mapView(MAPSIZE, MAPSIZE, PRADERA, renderer, textureLoader);

    int mouse_x = -1, mouse_y = -1;
    MousePosition mouse(mouse_x, mouse_y);

    std::string salida;
    if (argv[1])
        salida.append(argv[1]);
    else
        salida.append(SALIDA_DEFAULT);
    Editor editor(mapView, textureLoader, renderer, std::string(salida), window);

    EditorButtons buttons(mouse, renderer, editor, textureLoader);
    buttons.addInitialButtons();

    int tileX = 0;
    int tileY = 0;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    mouseMovement.entryMovement(event.motion.x, event.motion.y,
                                                event.motion.windowID);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    mouse.activate();
                    break;
                case SDL_FINGERDOWN:
                    mouse_x = static_cast<int>(event.tfinger.x);
                    mouse_y = static_cast<int>(event.tfinger.y);
                    mouse.activate();
                    break;
                case SDL_FINGERMOTION:
                    renderer.updateCameraFinger(static_cast<int>(event.tfinger.dx),
                                                static_cast<int>(event.tfinger.dy));
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y == 1) //scroll up
                        renderer.zoomIn();
                    else
                        renderer.zoomOut();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_PLUS:
                            renderer.zoomIn();
                            break;
                        case SDLK_MINUS:
                            renderer.zoomOut();
                            break;
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
            if (mouse.isActive()) {
                if (!buttons.isAnyClicked()) {
                    tileX = mapView.getTileXFromPixel(mouse_x, mouse_y);
                    tileY = mapView.getTileYFromPixel(mouse_x, mouse_y);
                    editor.applyTileFunction(tileX, tileY);
                    mouse.deactivate();
                }
            }
            event.type = 0;
        }
        renderer.clearRender();
        mouseMovement.doMovement();
        editor.draw();
        buttons.draw();
        renderer.present();
    }
    SDL_Quit();
    return 0;
}

