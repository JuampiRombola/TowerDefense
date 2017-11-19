#ifndef TOWERDEFENSE_DISMINUIRPADDINGBUTTON_H
#define TOWERDEFENSE_DISMINUIRPADDINGBUTTON_H


#include "../Common/Button.h"

class DisminuirPaddingButton : public Button {
private:
    unsigned int &padding;
    void click();

public:
    DisminuirPaddingButton(unsigned int &padding, SDL_Texture *texture,
                           MousePosition &mousePosition, Renderer &renderer);

};


#endif //TOWERDEFENSE_DISMINUIRPADDINGBUTTON_H
