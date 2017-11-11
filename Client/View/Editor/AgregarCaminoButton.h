#ifndef TOWERDEFENSE_AGREGARCAMINOBUTTON_H
#define TOWERDEFENSE_AGREGARCAMINOBUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class AgregarCaminoButton : public Button {
private:
    Editor &editor;
public:
    AgregarCaminoButton(SDL_Texture *texture,
                            MousePosition &mousePosition,
                            Renderer &renderer,
                            Editor &editor);
    void click();
};


#endif //TOWERDEFENSE_AGREGARCAMINOBUTTON_H
