#ifndef TOWERDEFENSE_NUEVAHORDABUTTON_H
#define TOWERDEFENSE_NUEVAHORDABUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class NuevaHordaButton : public Button {
private:
    Editor &editor;
    int idHorda;
    unsigned int &padding;
    std::function<void(int)> addButtonsFn;
    void click();

public:
    NuevaHordaButton(unsigned int &padding, SDL_Texture *texture,
                     MousePosition &mousePosition,
                     Renderer &renderer, Editor &editor,
                     std::function<void(int)> addButtonsFn);

};


#endif //TOWERDEFENSE_NUEVAHORDABUTTON_H
