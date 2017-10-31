#ifndef TOWERDEFENSE_DONOTHINGBUTTON_H
#define TOWERDEFENSE_DONOTHINGBUTTON_H

#include "Button.h"

// Esta clase es RECONTRA provisoria. No puede sobrevivir después del viernes
// 3/11. Es para que modificar ahora todos los Button* de la clase Buttons.
// Mañana veo con Martín porque tengo una banda de dudas de modelado con eso.
class DoNothingButton : public Button {
private:
    void click();
public:
    DoNothingButton(int id, int horda, SDL_Texture *texture,
                    MousePosition &mousePosition, Renderer &renderer);
};


#endif //TOWERDEFENSE_DONOTHINGBUTTON_H
