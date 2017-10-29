#ifndef TOWERDEFENSE_TOGGLEBUTTON_H
#define TOWERDEFENSE_TOGGLEBUTTON_H

#include "Button.h"

class ToggleButton : public Button {
private:
    SDL_Texture* activeTexture;
    SDL_Texture* inactiveTexture;
    void toggleTexture();
    void draw();
public:
    ToggleButton(int id, int posX, int posY, int width, int height, SDL_Texture
            *activeTexture, SDL_Texture* inactiveTexture, MousePosition
            &mousePosition, Renderer& renderer);
    ~ToggleButton();
};


#endif //TOWERDEFENSE_TOGGLEBUTTON_H
