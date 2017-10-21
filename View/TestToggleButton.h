#ifndef TOWERDEFENSE_TESTTOGGLEBUTTON_H
#define TOWERDEFENSE_TESTTOGGLEBUTTON_H

#include "ToggleButton.h"

class TestToggleButton : public ToggleButton {
private:
    void click();
public:
    TestToggleButton(int posX, int posY, int width, int height,
                     SDL_Texture *activeTexture, SDL_Texture *inactiveTexture,
                     MousePosition &mousePosition, Renderer &renderer);
    ~TestToggleButton();
};


#endif //TOWERDEFENSE_TESTTOGGLEBUTTON_H
