#ifndef TOWERDEFENSE_GAMEBUTTONS_H
#define TOWERDEFENSE_GAMEBUTTONS_H

#include <vector>
#include "../Common/Image.h"
#include "../Common/MousePosition.h"
#include "../Common/TextureLoader.h"
#include "MapView.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "PadlockButton.h"
#include "WaitActionButton.h"
#include "UpRightButton.h"

class GameButtons {
private:
    Window &window;
    MousePosition &mousePosition;
    Renderer &renderer;
    TextureLoader &textureLoader;
    int &cmd;
    std::vector<WaitActionButton*> towers;
    std::vector<WaitActionButton*> spells;
    std::vector<UpRightButton*> barUpRight;
    std::list<PadlockButton*> fakeButtons;
    Sprite decoTowers;
    Sprite decoSpells;

public:
    GameButtons(Window &w, MousePosition &mousePosition, Renderer &renderer,
                TextureLoader &textureLoader, int &cmd);
    ~GameButtons();
    void addTowerButtons(int key);
    bool isAnyClicked();
    bool isAnyFakeClicked();
    void draw();
    void initFakeButtons();
    bool exitClicked();
    void setCooldown(int key, Uint32 cd);
    void clickButton(SDL_Keycode sym);
};


#endif //TOWERDEFENSE_GAMEBUTTONS_H
