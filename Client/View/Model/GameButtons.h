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
    std::list<Image*> images;
    MousePosition &mousePosition;
    Renderer &renderer;
    TextureLoader &textureLoader;
    CommandDispatcher &dispatcher;
public:
    GameButtons(MousePosition &mousePosition, Renderer &renderer,
                    TextureLoader &textureLoader, CommandDispatcher &dispatcher);
    ~GameButtons();
    void addTowerButtons();
};


#endif //TOWERDEFENSE_GAMEBUTTONS_H
