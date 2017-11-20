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

class GameButtons {
private:
    Window &window;
    MousePosition &mousePosition;
    Renderer &renderer;
    TextureLoader &textureLoader;
    CommandDispatcher &dispatcher;
    int &cmd;
    std::list<Image*> towers;
    std::list<Image*> spells;
    std::list<Image*> barUpRight;

public:
    GameButtons(Window &w, MousePosition &mousePosition, Renderer &renderer,
                TextureLoader &textureLoader, CommandDispatcher &dispatcher,
                int &cmd);
    ~GameButtons();
    void addTowerButtons(int key);
    bool isAnyClicked();
    void draw();
};


#endif //TOWERDEFENSE_GAMEBUTTONS_H
