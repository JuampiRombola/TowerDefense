#ifndef TOWERDEFENSE_GUARDARBUTTON_H
#define TOWERDEFENSE_GUARDARBUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class GuardarButton : public Button {
private:
    Editor& editor;
    void click();

public:
    GuardarButton(SDL_Texture *texture,
                  MousePosition &mousePosition,
                  Renderer &renderer, Editor &editor);
};


#endif //TOWERDEFENSE_GUARDARBUTTON_H
