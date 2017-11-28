#include "Common/Window.h"
#include "Common/Renderer.h"
#include "Common/TextureLoader.h"
#include "Common/SpriteNamesConfig.h"
#include "Model/ModelView.h"
#include "Model/HudView.h"
#include "Model/ChatView.h"
#include "Common/MusicLoader.h"
#include "Common/MouseMovement.h"

#define TITLE "Tower Defense"

#define WINDOWWIDTH 1152
#define WINDOWHEIGHT 600
#define FPS 40

#define MAPSIZE 9

int main(int argc, char** argv) {
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    TTF_Init();
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT, 0);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), 0);
    MusicLoader musicLoader;
    musicLoader.playMusic();
    MusicPlayer musicPlayer(musicLoader);
    ModelView modelView(renderer, textureLoader, musicPlayer);
    modelView.setMapEnvironment(GELIDO);
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
    modelView.createPathTile(0, 0);
    modelView.createPathTile(0, 2);
    modelView.createPathTile(0, 3);
    modelView.createPathTile(0, 4);
    modelView.createPathTile(0, 5);
    modelView.createPathTile(0, 6);
    modelView.createPathTile(0, 7);
    modelView.createPathTile(0, 8);

    modelView.createPathTile(2, 2);
    modelView.createPathTile(2, 4);
    modelView.createPathTile(2, 5);
    modelView.createPathTile(2, 6);

    modelView.createPathTile(8, 0);
    modelView.createPathTile(8, 1);
    modelView.createPathTile(8, 2);
    modelView.createPathTile(8, 3);
    modelView.createPathTile(8, 4);
    modelView.createPathTile(8, 5);
    modelView.createPathTile(8, 6);
    modelView.createPathTile(8, 7);
    modelView.createPathTile(8, 8);

    modelView.createPathTile(6, 2);
    modelView.createPathTile(6, 3);
    modelView.createPathTile(6, 4);
    modelView.createPathTile(6, 5);
    modelView.createPathTile(6, 6);

    modelView.createPathTile(1, 0);
    modelView.createPathTile(2, 0);
    modelView.createPathTile(3, 0);
    modelView.createPathTile(4, 0);
    modelView.createPathTile(5, 0);
    modelView.createPathTile(6, 0);
    modelView.createPathTile(7, 0);

    modelView.createPathTile(3, 2);
    modelView.createPathTile(4, 2);
    modelView.createPathTile(5, 2);

    modelView.createPathTile(1, 8);
    modelView.createPathTile(2, 8);
    modelView.createPathTile(3, 8);
    modelView.createPathTile(4, 8);
    modelView.createPathTile(5, 8);
    modelView.createPathTile(6, 8);
    modelView.createPathTile(7, 8);

    modelView.createPathTile(3, 6);
    modelView.createPathTile(4, 6);
    modelView.createPathTile(5, 6);

    modelView.createStructureTile(1, 1);
    modelView.createStructureTile(7, 7);
    modelView.createStructureTile(1, 7);
    modelView.createStructureTile(7, 1);

    modelView.createStructureTile(3, 3);
    modelView.createStructureTile(5, 5);
    modelView.createStructureTile(3, 5);
    modelView.createStructureTile(5, 3);

    modelView.createPortalSalida(0, 0);
    modelView.createPortalSalida(2, 2);
    modelView.createPortalEntrada(0, 2);
    modelView.createPortalEntrada(2, 4);

    //modelView.createTower(1, TORRE_TIERRA, 2, 0);
    //modelView.createTower(2, TORRE_AIRE, 2, 2);
    //modelView.createTower(3, TORRE_FUEGO, 1, 4);
    //modelView.createTower(4, TORRE_AGUA, 4, 6);

    // Dispatcher
    SocketWrapper fd(-1);
    CommandDispatcher cmdDispatcher(fd);

    // HUD
    HudView hudView(window, textureLoader, renderer, cmdDispatcher,modelView);
    hudView.addElementalButtons(ELEMENTAL_EARTH);
    //hudView.addElementalButtons(ELEMENTAL_FIRE);
    //hudView.addElementalButtons(ELEMENTAL_WATER);
    //hudView.addElementalButtons(ELEMENTAL_AIR);

    ChatView chat(cmdDispatcher, window, renderer, textureLoader);

    MouseMovement mouseMovement(renderer);

    TowerView towerView(0, TORRE_FUEGO, textureLoader, renderer);


    modelView.createTower(1, TORRE_FUEGO, 1, 1);
    modelView.createTower(2, TORRE_AGUA, 3, 3);
    modelView.createTower(3, TORRE_TIERRA, 5, 5);
    modelView.createTower(4, TORRE_AIRE, 3, 5);

    UnitView unit(0, ABOMINABLE, textureLoader, renderer);
    unit.setSpeed(5000);
    unit.move(0, 2, 0, 3);

    Uint32 t1;
    Uint32 t2;
    Uint32 s = 1000 / FPS;
    Uint32 delta = 0;
    Uint32 elapsedTime = 0;
    Uint32 delayTime = 0;

    while (!hudView.exitActive()) {
        t1 = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    hudView.enableExitView();
                    break;
                case SDL_MOUSEMOTION:
                    mouseMovement.entryMovement(event.motion.x,
                                                event.motion.y,
                                                event.motion.windowID);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    hudView.getMouseButtonDown(); break;
                case SDL_MOUSEBUTTONUP:
                    hudView.getMouseState(); break;
                case SDL_FINGERDOWN:
                    hudView.getFingerButtonDown(event); break;
                case SDL_FINGERUP:
                    hudView.getFingerState(event); break;
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
                case SDL_TEXTINPUT: {
                    if (chat.isActive()) {
                        std::string text(event.text.text);
                        chat.newInput(text);
                    }
                    break;
                }
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                            if (chat.isActive())
                                chat.disable();
                            else
                                chat.enable();
                            break;
                        case SDLK_BACKSPACE:
                            if (chat.isActive())
                                chat.erase();
                            break;
                        case SDLK_ESCAPE:
                            if (hudView.isExitViewEnable())
                                hudView.disableExitView();
                            else
                                hudView.enableExitView();
                            break;
                        case SDLK_a:
                            unit.setSpeed(10000);
                            break;
                        case SDLK_s:
                            unit.setSpeed(5000);
                            break;
                        case SDLK_d:
                            unit.totalFreeze(2000);
                            break;
                        case SDLK_z:
                            unit.move(0, 3, 0, 4);
                            break;
                        case SDLK_x:
                            unit.move(0, 4, 0, 5);
                            break;
                        case SDLK_c:
                            unit.move(0, 5, 0, 6);
                            break;
                        case SDLK_v:
                            unit.move(0, 6, 1, 6);
                            break;
                        case SDLK_LEFT:
                            renderer.updateCamera(-1, 0); break;
                        case SDLK_RIGHT:
                            renderer.updateCamera(1, 0); break;
                        case SDLK_UP:
                            renderer.updateCamera(0, -1); break;
                        case SDLK_DOWN:
                            renderer.updateCamera(0, 1); break;
                        default: break;
                    }
            }
            hudView.doMouseAction();
        }
        renderer.clearRender();
        mouseMovement.doMovement();

        modelView.draw(SDL_GetTicks());
        hudView.draw();
        chat.draw();
        unit.draw(SDL_GetTicks());

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
    TTF_Quit();
    SDL_Quit();
}
