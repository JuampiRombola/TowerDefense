#ifndef TOWERDEFENSE_TESTBUTTON_H
#define TOWERDEFENSE_TESTBUTTON_H

#include "Button.h"

class TestButton : public Button {
private:
    void click();
public:
    TestButton(int posX, int posY, int width, int height, SDL_Texture *texture,
               MousePosition &mousePosition, Renderer &renderer);
    ~TestButton();
};


#endif //TOWERDEFENSE_TESTBUTTON_H
