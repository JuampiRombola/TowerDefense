#ifndef TOWERDEFENSE_AGREGARPORTALSALIDABUTTON_H
#define TOWERDEFENSE_AGREGARPORTALSALIDABUTTON_H


#include "Editor.h"
#include "../Common/MousePosition.h"
#include "../Common/Button.h"

class AgregarPortalSalidaButton : public Button {
private:
    Editor &editor;
public:
    AgregarPortalSalidaButton(SDL_Texture *texture,
                                  MousePosition &mousePosition, Renderer &renderer,
                                  Editor &editor);

    void click();
};


#endif //TOWERDEFENSE_AGREGARPORTALSALIDABUTTON_H
