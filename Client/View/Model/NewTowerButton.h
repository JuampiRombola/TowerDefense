#ifndef TOWERDEFENSE_NEWTOWERBUTTON_H
#define TOWERDEFENSE_NEWTOWERBUTTON_H

#include "../Common/Button.h"
#include "MapView.h"
#include "ViewConstants.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "GameButtons.h"

class NewTowerButton : public Button {
private:
    const int element;
    int &command;
    Image transparency;

public:
    NewTowerButton(Window &w, int element, int &cmd, SDL_Texture *texture,
                   SDL_Texture *transp, MousePosition &mousePosition,
                   Renderer &renderer, int n);
    void draw(int number) override;
    void click() override;
};


#endif //TOWERDEFENSE_NEWTOWERBUTTON_H
