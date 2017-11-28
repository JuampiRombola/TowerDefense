#ifndef TOWERDEFENSE_SALIDABUTTON_H
#define TOWERDEFENSE_SALIDABUTTON_H


#include "../Common/Button.h"
#include "Editor.h"

class SalidaButton : public Button {
private:
    Editor& editor;
    void click();

public:
    SalidaButton(SDL_Texture *texture,
                  MousePosition &mousePosition,
                  Renderer &renderer, Editor &editor);

};


#endif //TOWERDEFENSE_SALIDABUTTON_H
