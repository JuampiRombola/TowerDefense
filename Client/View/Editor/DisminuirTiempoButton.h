#ifndef TOWERDEFENSE_DISMINUIRTIEMPOBUTTON_H
#define TOWERDEFENSE_DISMINUIRTIEMPOBUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class DisminuirTiempoButton : public Button {
private:
    int horda;
    Editor &editor;

    void click();

public:
    DisminuirTiempoButton(int horda,
                         SDL_Texture *texture,
                         MousePosition &mousePosition,
                         Renderer &renderer,
                         Editor &editor);
    void draw(int number);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_DISMINUIRTIEMPOBUTTON_H
