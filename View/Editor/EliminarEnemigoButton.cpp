#include <iostream>
#include "EliminarEnemigoButton.h"

EliminarEnemigoButton::EliminarEnemigoButton(int horda,
                                             const std::string &enemigo,
                                             SDL_Texture *texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor)
        : Button(0, 0, HORDA_MODIFY_QUANTITY_SIZE, HORDA_MODIFY_QUANTITY_SIZE,
                 texture, mousePosition, renderer), horda(horda),
          enemigo(enemigo), editor(editor) {}

void EliminarEnemigoButton::click() {
    editor.eliminarEnemigo(horda, enemigo);
}

void EliminarEnemigoButton::draw(int number) {
    div_t division = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    button.x = 0;
    button.y =
            HORDA_MODIFY_QUANTITY_PADDING + division.quot * HORDA_TOTAL_HEIGHT;
    Button::draw(number);
}
