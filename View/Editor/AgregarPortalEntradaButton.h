#ifndef TOWERDEFENSE_AGREGARPORTALENTRADABUTTON_H
#define TOWERDEFENSE_AGREGARPORTALENTRADABUTTON_H

#include "Button.h"
#include "Editor.h"

class AgregarPortalEntradaButton : public Button {
private:
    Editor& editor;
public:
    AgregarPortalEntradaButton(SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer,
                                   Editor &editor);
    void click();
};


#endif //TOWERDEFENSE_AGREGARPORTALENTRADABUTTON_H
