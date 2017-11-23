#ifndef TOWERDEFENSE_HUDVIEW_H
#define TOWERDEFENSE_HUDVIEW_H


#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/MousePosition.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "../../include/NetCommands/ClientBuildTowerCommand.h"
#include "../../include/NetCommands/ClientCastSpellCommand.h"
#include "GameButtons.h"
#include "ViewConstants.h"
#include "UpgradeView.h"
#include "ModelView.h"
#include "ExitView.h"

class HudView {
private:
    TextureLoader &textureLoader;
    Renderer &renderer;
    CommandDispatcher &dispatcher;
    int mouse_x;
    int mouse_y;
    MousePosition mousePosition;
    int currentCommand;
    GameButtons buttons;
    SDL_Cursor *arrow;
    SDL_Cursor *crosshair;
    ModelView &model;
    UpgradeView *upgradeTarget;
    bool exit;
    ExitView exitView;

public:
    HudView(Window &w, TextureLoader &tl, Renderer &r,
            CommandDispatcher &cd, ModelView &model);
    ~HudView();
    void getMouseState();
    void getFingerState(SDL_Event &event);
    void doMouseAction();
    void sendCommand(int x, int y);
    void draw();
    void addElementalButtons(int key);
    void getMouseButtonDown();
    void getFingerButtonDown(SDL_Event &event);
    void updateTarget(TowerView *target);
    bool exitActive();
    bool isExitViewEnable();
    void enableExitView();
    void disableExitView();

};


#endif //TOWERDEFENSE_HUDVIEW_H
