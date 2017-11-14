#ifndef TOWERDEFENSE_HUDVIEW_H
#define TOWERDEFENSE_HUDVIEW_H


#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/MousePosition.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "../../include/NetCommands/MapCommand.h"
#include "GameButtons.h"
#include "ViewConstants.h"

class HudView {
private:
    TextureLoader &textureLoader;
    Renderer &renderer;
    CommandDispatcher &dispatcher;
    int mouse_x;
    int mouse_y;
    MousePosition mousePosition;
    GameButtons buttons;
    int currentCommand;

public:
    HudView(Window &w, TextureLoader &tl, Renderer &r,
            CommandDispatcher &cd);
    void getMouseState();
    void getFingerState(SDL_Event &event);
    void doMouseAction();
    void sendCommand(int x, int y);
    void draw();
    void addElementalButtons(int key);

};


#endif //TOWERDEFENSE_HUDVIEW_H
