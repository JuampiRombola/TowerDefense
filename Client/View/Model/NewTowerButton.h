#ifndef TOWERDEFENSE_NEWTOWERBUTTON_H
#define TOWERDEFENSE_NEWTOWERBUTTON_H

#include "../Common/Button.h"
#include "MapView.h"
#include "ViewConstants.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "GameButtons.h"

class NewTowerButton : public Button {
private:
    const std::string element;
    CommandDispatcher &dispatcher;
public:
    NewTowerButton(std::string element, SDL_Texture *texture,
                       MousePosition &mousePosition, Renderer &renderer,
                       CommandDispatcher &dispatcher);
    void draw(int number);
    void click();
    void throwCommand(int tileX, int tileY);
};


#endif //TOWERDEFENSE_NEWTOWERBUTTON_H
