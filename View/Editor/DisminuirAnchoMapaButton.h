#ifndef TOWERDEFENSE_DISMINUIRANCHOMAPABUTTON_H
#define TOWERDEFENSE_DISMINUIRANCHOMAPABUTTON_H


#include "Editor.h"
#include "../Common/Button.h"

class DisminuirAnchoMapaButton : public Button {
private:
    Editor &editor;

    void click();

public:
    DisminuirAnchoMapaButton(SDL_Texture *texture,
    MousePosition &mousePosition,
            Renderer &renderer,
    Editor &editor);
};


#endif //TOWERDEFENSE_DISMINUIRANCHOMAPABUTTON_H
