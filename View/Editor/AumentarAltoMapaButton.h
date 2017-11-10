#ifndef TOWERDEFENSE_AUMENTARALTOMAPABUTTON_H
#define TOWERDEFENSE_AUMENTARALTOMAPABUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class AumentarAltoMapaButton : public Button {
private:
    Editor &editor;

    void click();

public:
    AumentarAltoMapaButton(SDL_Texture *texture,
                         MousePosition &mousePosition,
                         Renderer &renderer,
                         Editor &editor);
};


#endif //TOWERDEFENSE_AUMENTARALTOMAPABUTTON_H
