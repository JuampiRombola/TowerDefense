#ifndef TOWERDEFENSE_ELIMINARHORDABUTTON_H
#define TOWERDEFENSE_ELIMINARHORDABUTTON_H

#include "Button.h"
#include "Editor.h"

class EliminarHordaButton : public Button {
private:
    Editor &editor;
    int horda;

    void click();

public:
    EliminarHordaButton(int id, int horda, SDL_Texture *texture,
                        MousePosition &mousePosition, Renderer &renderer,
                        Editor &editor);
};

#endif //TOWERDEFENSE_ELIMINARHORDABUTTON_H
