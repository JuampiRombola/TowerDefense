#ifndef TOWERDEFENSE_CONTADORTIEMPOHORDA_H
#define TOWERDEFENSE_CONTADORTIEMPOHORDA_H

#include "../Common/Text.h"
#include "Editor.h"

class ContadorTiempoHordaInput : public Text {
private:
    int horda;
    Editor &editor;
public:
    ContadorTiempoHordaInput(int horda, SDL_Texture *texture,
                          Renderer &renderer, Editor &editor);

    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_CONTADORTIEMPOHORDA_H
