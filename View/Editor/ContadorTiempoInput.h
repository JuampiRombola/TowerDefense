#ifndef TOWERDEFENSE_CONTADORTIEMPOHORDA_H
#define TOWERDEFENSE_CONTADORTIEMPOHORDA_H

#include "../Common/Text.h"
#include "Editor.h"

class ContadorTiempoInput : public Text {
private:
    int horda;
    Editor &editor;
public:
    ContadorTiempoInput(int horda, SDL_Texture *texture,
                          Renderer &renderer, Editor &editor);

    void draw(int number);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_CONTADORTIEMPOHORDA_H
