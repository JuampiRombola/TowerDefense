#ifndef TOWERDEFENSE_DISMINUIRALTOMAPABUTTON_H
#define TOWERDEFENSE_DISMINUIRALTOMAPABUTTON_H


#include "Button.h"
#include "Editor.h"

class DisminuirAltoMapaButton : public Button {
private:
    Editor &editor;

    void click();

public:
    DisminuirAltoMapaButton(SDL_Texture *texture,
    MousePosition &mousePosition,
            Renderer &renderer,
    Editor &editor);
};


#endif //TOWERDEFENSE_DISMINUIRALTOMAPABUTTON_H
