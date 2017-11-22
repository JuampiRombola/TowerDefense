#ifndef TOWERDEFENSE_DISMINUIRTIEMPOENEMIGOSBUTTON_H
#define TOWERDEFENSE_DISMINUIRTIEMPOENEMIGOSBUTTON_H


#include "../Common/Button.h"
#include "Editor.h"

class DisminuirTiempoEnemigosButton : public Button {
private:
    int horda;
    Editor &editor;

    void click();

public:
    DisminuirTiempoEnemigosButton(int horda, SDL_Texture *texture,
                                  MousePosition &mousePosition,
                                  Renderer &renderer, Editor &editor);

    void draw(int number, int padding);

    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_DISMINUIRTIEMPOENEMIGOSBUTTON_H
