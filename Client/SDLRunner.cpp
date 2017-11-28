#include "SDLRunner.h"
#include "include/NetCommands/CommandDispatcher.h"
#include "include/NetCommands/ChatMessageCommand.h"
#include "include/NotificationReciever.h"
#include "include/ClientSocket.h"
#include "View/Model/ModelView.h"
#include "View/Model/ViewConstants.h"
#include "View/Model/HudView.h"
#include "View/Model/ChatView.h"
#include "include/NetCommands/PlayerLoadedGameCommand.h"
#include "include/NetCommands/LoadMapCommand.h"
#include "View/Common/MusicLoader.h"
#include "View/Common/MouseMovement.h"
#include "View/Common/MusicPlayer.h"

#define TITLE "Tower Defense"

#define CONFIG_PATH "windowConfig.yaml"

SDLRunner::SDLRunner(uint8_t mapSurface, uint32_t mapWidth, uint32_t mapHeight)
: _mapSurface(mapSurface), _mapWidth(mapWidth), _mapHeight(mapHeight)
{

}

SDLRunner::~SDLRunner() {
    delete _dispatcher;
    delete _reciever;
    delete _lobbyManager;
    delete _sock;
}

void SDLRunner::Run(CommandDispatcher* dispatcher, NotificationReciever* reciever, ClientLobbyManager* lobbyManager, ClientSocket* sock)
{
    _dispatcher = dispatcher;
    _lobbyManager = lobbyManager;
    _reciever = reciever;
    _sock = sock;

    SDL_Event event{};
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    TTF_Init();
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    YAML::Node windowConfig(YAML::LoadFile(CONFIG_PATH));
    Window window(TITLE, windowConfig["game_width"].as<int>(),
                  windowConfig["game_height"].as<int>(),
                  windowConfig["game_fullscreen"].as<bool>() ? SDL_WINDOW_FULLSCREEN_DESKTOP
                                                               : SDL_WINDOW_FOREIGN);
    Renderer renderer(window, _mapWidth, _mapHeight);
    MusicLoader musicLoader;
    musicLoader.playMusic();
    MusicPlayer musicPlayer(musicLoader);
    TextureLoader textureLoader(renderer.getRenderer(), 0);
    ModelView modelView(renderer, textureLoader, musicPlayer);
    HudView hudView(window, textureLoader, renderer, *_dispatcher, modelView);
    ChatView chat(*_dispatcher, window, renderer, textureLoader);
    MouseMovement mouseMovement(renderer);

    _reciever->model_view =  &modelView;
    _reciever->hud_view = &hudView;
    _reciever->chat_view = &chat;

    _dispatcher->QueueCommand(new LoadMapCommand());
    
    modelView.setMapEnvironment(_mapSurface);
    modelView.setMapWidthHeight(_mapWidth, _mapHeight);

    if (_lobbyManager->groundHUDEnabled)
        hudView.addElementalButtons(ELEMENTAL_EARTH);
    if (lobbyManager->fireHUDEnabled)
        hudView.addElementalButtons(ELEMENTAL_FIRE);
    if (lobbyManager->waterHUDEnabled)
        hudView.addElementalButtons(ELEMENTAL_WATER);
    if (lobbyManager->airHUDEnabled)
        hudView.addElementalButtons(ELEMENTAL_AIR);

    Uint32 t1;
    Uint32 t2;
    Uint32 s = 1000 / windowConfig["game_fps"].as<uint>();
    Uint32 delta = 0;
    Uint32 elapsedTime = 0;
    Uint32 delayTime = 0;


    std::unique_lock<std::mutex> lock(modelView.mapLoadedMutex);
    while(!modelView.mapLoaded)
        modelView.mapLoadedCondVariable.wait(lock);


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
                    renderer.updateCameraFinger(
                            static_cast<int>(event.tfinger.dx),
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
                        case SDLK_q: 
                        case SDLK_w: 
                        case SDLK_e: 
                        case SDLK_r:
                        case SDLK_f:
                        case SDLK_1:
                        case SDLK_2:
                        case SDLK_3:
                        case SDLK_4: 
                        case SDLK_5:
                        case SDLK_6:
                        case SDLK_7: 
                        case SDLK_8:
                            if (!chat.isActive())
                                hudView.clickButton(event.key.keysym.sym);
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
                    break;
                case SDL_TEXTINPUT:
                    if (chat.isActive() ) {
                        std::string text(event.text.text);
                        chat.newInput(text);
                    }
                    break;
            }
            hudView.doMouseAction();
        }
        renderer.clearRender();
        mouseMovement.doMovement();

        modelView.draw(SDL_GetTicks());
        hudView.draw();
        chat.draw();
        musicPlayer.playMusic();

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

    _reciever->Stop();
    _dispatcher->Stop();
    
    TTF_Quit();
    SDL_Quit();



}
