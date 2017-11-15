#include "SDLRunner.h"
#include "include/NetCommands/CommandDispatcher.h"
#include "include/NotificationReciever.h"
#include "include/ClientSocket.h"
#include "View/Model/ModelView.h"
#include "View/Model/ViewConstants.h"
#include "View/Model/HudView.h"

#define TITLE "Tower Defense"

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480
#define FPS 40

#define MAPSIZE 7

SDLRunner::SDLRunner() {

}
SDLRunner::~SDLRunner() {
    delete _dispatcher;
    delete _reciever;
    delete _lobbyManager;
    std::cout << "lobbymanager deleted\n" << std::flush;
    delete _sock;
    std::cout << "sock deleted\n" << std::flush;
}

void SDLRunner::Run(CommandDispatcher* dispatcher, NotificationReciever* reciever, ClientLobbyManager* lobbyManager, ClientSocket* sock)
{
    bool quit = false;
    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO);
    Window window(TITLE, WINDOWWIDTH, WINDOWHEIGHT);
    Renderer renderer(window, MAPSIZE, MAPSIZE);
    TextureLoader textureLoader(renderer.getRenderer(), 0);

    _dispatcher = dispatcher;
    _lobbyManager = lobbyManager;
    _reciever = reciever;
    _sock = sock;

    ModelView modelView(renderer, textureLoader);
    _reciever->model_view =  &modelView;

    modelView.setMapEnvironment(GELIDO);
    modelView.setMapWidthHeight(MAPSIZE, MAPSIZE);

    modelView.createPathTile(3, 6);
    modelView.createPathTile(3, 5);
    modelView.createPathTile(3, 4);
    modelView.createPathTile(3, 3);
    modelView.createPathTile(3, 2);
    modelView.createPathTile(2, 2);
    modelView.createPathTile(1, 2);
    modelView.createPathTile(0, 2);

    modelView.createStructureTile(5, 0);
    modelView.createStructureTile(5, 2);
    modelView.createStructureTile(5, 4);
    modelView.createStructureTile(5, 6);

    HudView hudView(window, textureLoader, renderer, *_dispatcher);
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

    while (!quit && _reciever->Running()) {
        t1 = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true; break;
                case SDL_MOUSEBUTTONDOWN:
                    hudView.getMouseState();
                    break;
                case SDL_FINGERDOWN:
                    hudView.getFingerState(event);
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
