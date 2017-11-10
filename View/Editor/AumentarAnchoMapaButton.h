#ifndef TOWERDEFENSE_AUMENTARANCHOMAPABUTTON_H
#define TOWERDEFENSE_AUMENTARANCHOMAPABUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class AumentarAnchoMapaButton : public Button {
private:
    Editor &editor;

    void click();

public:
    AumentarAnchoMapaButton(SDL_Texture *texture,
    MousePosition &mousePosition,
            Renderer &renderer,
    Editor &editor);
};


#endif //TOWERDEFENSE_AUMENTARANCHOMAPABUTTON_H
