#ifndef TOWERDEFENSE_ELIMINARHORDABUTTON_H
#define TOWERDEFENSE_ELIMINARHORDABUTTON_H

#include "Button.h"
#include "Editor.h"

class EliminarHordaButton : public Button {
private:
    Editor &editor;
    int horda;
    std::function<void(int)> deleteButtonsFn;
    void click();

public:
    EliminarHordaButton(int horda, SDL_Texture *texture,
                            MousePosition &mousePosition, Renderer &renderer,
                            Editor &editor,
                            std::function<void(int)> deleteButtonsFn);
    void draw(int number);
};

#endif //TOWERDEFENSE_ELIMINARHORDABUTTON_H
