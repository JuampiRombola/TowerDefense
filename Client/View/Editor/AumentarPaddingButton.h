#ifndef TOWERDEFENSE_AGREGARPADDINGBUTTON_H
#define TOWERDEFENSE_AGREGARPADDINGBUTTON_H


#include "../Common/Button.h"

class AumentarPaddingButton : public Button {
private:
    unsigned int &padding;
    void click();

public:
    AumentarPaddingButton(unsigned int &padding, SDL_Texture *texture,
                           MousePosition &mousePosition, Renderer &renderer);

};


#endif //TOWERDEFENSE_AGREGARPADDINGBUTTON_H
