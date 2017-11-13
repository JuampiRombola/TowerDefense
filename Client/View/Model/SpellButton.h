#ifndef TOWERDEFENSE_SPELLBUTTON_H
#define TOWERDEFENSE_SPELLBUTTON_H


#include "../Common/MousePosition.h"
#include "../Common/Button.h"

class SpellButton : public Button {
private:
    const int type;
    int &command;
public:
    SpellButton(Window &w, int type, int &cmd, SDL_Texture *texture,
    MousePosition &mousePosition, Renderer &renderer,
    int n);
    void draw();
    void click() override;
};


#endif //TOWERDEFENSE_SPELLBUTTON_H
