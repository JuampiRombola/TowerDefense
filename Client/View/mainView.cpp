#include "Common/Window.h"
#include "Common/Renderer.h"
#include "Common/TextureLoader.h"
#include "Common/SpriteNamesConfig.h"
#include "Model/ModelView.h"
#include "Model/HudView.h"

#define TITLE "Tower Defense"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480
#define FPS 40

#define MAPSIZE 15

int main(int argc, char** argv) {
    bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), 0);

    ModelView modelView(renderer, textureLoader);
    modelView.setMapEnvironment(DESIERTO);
    modelView.setMapWidthHeight(MAPSIZE, MAPSIZE);
    /*modelView.setMapWidthHeight(MAPSIZE, MAPSIZE);
    modelView.createPathTile(0, 0);
    modelView.createPathTile(1, 0);
    modelView.createPathTile(1, 1);
    modelView.createPathTile(2, 1);
    modelView.createPathTile(3, 1);
    modelView.createPathTile(3, 2);
    modelView.createPathTile(3, 3);
    modelView.createPathTile(2, 3);
    modelView.createPathTile(2, 4);
    modelView.createPathTile(2, 5);
    modelView.createPathTile(3, 5);
    modelView.createPathTile(4, 5);
    modelView.createPathTile(5, 5);
    modelView.createPathTile(6, 5);
    modelView.createPathTile(6, 6);

    modelView.createStructureTile(1, 4);
    modelView.createStructureTile(2, 0);
    modelView.createStructureTile(2, 2);
    modelView.createStructureTile(3, 4);
    modelView.createStructureTile(4, 6);

    modelView.createPortalEntrada(0, 0);
    modelView.createPortalSalida(6, 6);
*/
    modelView.createPathTile(0, 3);
    modelView.createPathTile(1, 3);
    modelView.createPathTile(2, 3);
    modelView.createPathTile(4, 3);
    modelView.createPathTile(5, 3);
    modelView.createPathTile(3, 3);
    modelView.createPathTile(6, 3);
    modelView.createPathTile(7, 3);
    modelView.createPathTile(8, 3);
    modelView.createPathTile(9, 3);
    modelView.createPathTile(10, 3);
    modelView.createPathTile(11, 3);
    modelView.createPathTile(12, 3);
    modelView.createPathTile(13, 3);
    modelView.createPathTile(14, 3);

    modelView.createPathTile(0, 7);
    modelView.createPathTile(1, 7);
    modelView.createPathTile(2, 7);
    modelView.createPathTile(3, 7);
    modelView.createPathTile(4, 7);
    modelView.createPathTile(5, 7);
    modelView.createPathTile(6, 7);
    modelView.createPathTile(7, 7);
    modelView.createPathTile(8, 7);
    modelView.createPathTile(9, 7);
    modelView.createPathTile(10, 7);
    modelView.createPathTile(11, 7);
    modelView.createPathTile(12, 7);
    modelView.createPathTile(13, 7);
    modelView.createPathTile(14, 7);

    modelView.createPathTile(0, 11);
    modelView.createPathTile(1, 11);
    modelView.createPathTile(2, 11);
    modelView.createPathTile(3, 11);
    modelView.createPathTile(4, 11);
    modelView.createPathTile(5, 11);
    modelView.createPathTile(6, 11);
    modelView.createPathTile(7, 11);
    modelView.createPathTile(8, 11);
    modelView.createPathTile(9, 11);
    modelView.createPathTile(10, 11);
    modelView.createPathTile(11, 11);
    modelView.createPathTile(12, 11);
    modelView.createPathTile(13, 11);
    modelView.createPathTile(14, 11);

    modelView.createStructureTile(1, 1);
    modelView.createStructureTile(1, 5);
    modelView.createStructureTile(1, 9);
    modelView.createStructureTile(1, 13);

    modelView.createStructureTile(5, 1);
    modelView.createStructureTile(5, 5);
    modelView.createStructureTile(5, 9);
    modelView.createStructureTile(5, 13);

    modelView.createStructureTile(8, 1);
    modelView.createStructureTile(8, 5);
    modelView.createStructureTile(8, 9);
    modelView.createStructureTile(8, 13);

    modelView.createStructureTile(11, 1);
    modelView.createStructureTile(11, 5);
    modelView.createStructureTile(11, 9);
    modelView.createStructureTile(11, 13);

    modelView.createTower(1, TORRE_TIERRA, 2, 0);
    modelView.createTower(2, TORRE_AIRE, 2, 2);
    modelView.createTower(3, TORRE_FUEGO, 1, 4);
    modelView.createTower(4, TORRE_AGUA, 4, 6);

    // Dispatcher
    SocketWrapper fd(0);
    CommandDispatcher cmdDispatcher(fd);

    // HUD
    HudView hudView(window, textureLoader, renderer, cmdDispatcher);
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
    while (!quit) {
        t1 = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT: quit = true; break;
                case SDL_MOUSEBUTTONDOWN:
                    hudView.getMouseState();
                    break;
                case SDL_FINGERDOWN:
                    hudView.getFingerState(event);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: quit = true; break;
                        case SDLK_i: renderer.zoomIn(); break;
                        case SDLK_o: renderer.zoomOut(); break;
                        case SDLK_d: modelView.killUnit(1); break;
                        case SDLK_s: modelView.createShot(
                                    DISPARO_TIERRA, 2, 0, 0, 0, 500);break;
                        case SDLK_a: modelView.createSpell(
                                    FIREWALL, 1, 1, 5000);break;
                        case SDLK_q: modelView.createUnit(
                                    ++idUnit, ABOMINABLE, 0, 0, 1, 0, 3000);
                            break;
                        case SDLK_z: modelView.moveUnit(1, 1, 0, 1, 1, 3000);
                            break;
                        case SDLK_x: modelView.moveUnit(1, 1, 1, 2, 1, 3000);
                            break;
                        case SDLK_c: modelView.moveUnit(1, 2, 1, 3, 1, 3000);
                            break;
                        case SDLK_v: modelView.moveUnit(1, 3, 1, 3, 2, 3000);
                            break;
                        case SDLK_b: modelView.moveUnit(1, 3, 2, 3, 3, 3000);
                            break;
                        case SDLK_n: modelView.moveUnit(1, 3, 3, 2, 3, 3000);
                            break;
                        case SDLK_m: modelView.moveUnit(1, 2, 3, 2, 4, 3000);
                            break;
                        case SDLK_LEFT: renderer.updateCamera(-1, 0); break;
                        case SDLK_RIGHT: renderer.updateCamera(1, 0); break;
                        case SDLK_UP: renderer.updateCamera(0, -1); break;
                        case SDLK_DOWN: renderer.updateCamera(0, 1); break;
                    }
            }
            hudView.doMouseAction();
        }
        renderer.clearRender();

        modelView.draw(SDL_GetTicks());
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
}
