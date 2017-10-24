#ifndef TOWERDEFENSE_NUEVAHORDABUTTON_H
#define TOWERDEFENSE_NUEVAHORDABUTTON_H

#include "Button.h"
#include "Editor.h"

class NuevaHordaButton : public Button {
private:
    Editor &editor;
    void click();
public:
    NuevaHordaButton(SDL_Texture *texture, MousePosition &mousePosition,
                     Renderer& renderer, Editor &editor);
    ~NuevaHordaButton();
};


#endif //TOWERDEFENSE_NUEVAHORDABUTTON_H
