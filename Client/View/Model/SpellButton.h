#ifndef TOWERDEFENSE_SPELLBUTTON_H
#define TOWERDEFENSE_SPELLBUTTON_H


#include "../Common/MousePosition.h"
#include "../Common/Button.h"

class SpellButton : public Button {
private:
    const int type;
    int &command;
    Image transparency;

public:
    SpellButton(Window &w, int element, int &cmd, SDL_Texture *texture,
                SDL_Texture *transp, MousePosition &mousePosition,
                Renderer &renderer, int n);
    void draw(int number, int padding) override;
    void click() override;
};


#endif //TOWERDEFENSE_SPELLBUTTON_H
