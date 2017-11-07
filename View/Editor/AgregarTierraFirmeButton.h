#ifndef TOWERDEFENSE_AGREGARTIERRAFIRMEBUTTON_H
#define TOWERDEFENSE_AGREGARTIERRAFIRMEBUTTON_H


#include "Button.h"
#include "Editor.h"

class AgregarTierraFirmeButton : public Button {
private:
    Editor &editor;
public:
    AgregarTierraFirmeButton(SDL_Texture *texture,
                                 MousePosition &mousePosition,
                                 Renderer &renderer,
                                 Editor &editor);
    void click();
};


#endif //TOWERDEFENSE_AGREGARTIERRAFIRMEBUTTON_H
