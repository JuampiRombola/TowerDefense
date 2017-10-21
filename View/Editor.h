#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include "Renderer.h"
#include "Buttons.h"

class Editor {
private:
    Renderer &renderer;
    Buttons &buttons;
public:
    Editor(Renderer& renderer, Buttons &buttons);
    ~Editor();
    void draw();
};


#endif //TOWERDEFENSE_EDITOR_H
