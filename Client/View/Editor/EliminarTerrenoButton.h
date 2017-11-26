#ifndef TOWERDEFENSE_ELIMINARTERRENOBUTTON_H
#define TOWERDEFENSE_ELIMINARTERRENOBUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class EliminarTerrenoButton : public Button {
private:
    Editor &editor;
public:
    EliminarTerrenoButton(SDL_Texture *texture, MousePosition &mousePosition, Renderer &renderer,
                          Editor &editor);

    void click();
};


#endif //TOWERDEFENSE_ELIMINARTERRENOBUTTON_H
