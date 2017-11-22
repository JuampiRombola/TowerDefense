#ifndef TOWERDEFENSE_GAMEBUTTONS_H
#define TOWERDEFENSE_GAMEBUTTONS_H

#include <list>
#include "../Common/Image.h"
#include "../Common/MousePosition.h"
#include "../Common/TextureLoader.h"
#include "MapView.h"
#include "NewTowerButton.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "PadlockButton.h"
#include "WaitActionButton.h"

class GameButtons {
private:
    Window &window;
    MousePosition &mousePosition;
    Renderer &renderer;
    TextureLoader &textureLoader;
    int &cmd;
    std::list<WaitActionButton*> towers;
    std::list<WaitActionButton*> spells;
    std::list<Image*> barUpRight;
    std::list<PadlockButton *> fakeButtons;
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
};


#endif //TOWERDEFENSE_GAMEBUTTONS_H
