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

#define MAPSIZE 15

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

    modelView.createStructureTile(9, 1);
    modelView.createStructureTile(9, 5);
    modelView.createStructureTile(9, 9);
    modelView.createStructureTile(9, 13);

    modelView.createStructureTile(13, 1);
    modelView.createStructureTile(13, 5);
    modelView.createStructureTile(13, 9);
    modelView.createStructureTile(13, 13);

    modelView.createPortalEntrada(0, 3);
    modelView.createPortalEntrada(0, 7);
    modelView.createPortalEntrada(0, 11);

    modelView.createPortalSalida(14, 3);
    modelView.createPortalSalida(14, 7);
    modelView.createPortalSalida(14, 11);

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
