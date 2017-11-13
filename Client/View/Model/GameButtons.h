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
    std::list<Image*> towers;
    std::list<Image*> spells;

public:
    GameButtons(Window &w, MousePosition &mousePosition, Renderer &renderer,
                TextureLoader &textureLoader, CommandDispatcher &dispatcher);
    ~GameButtons();
    void addTowerButtons(int key, int &cmd);
    bool isAnyClicked();
    void draw();
};


#endif //TOWERDEFENSE_GAMEBUTTONS_H
