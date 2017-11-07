#include <stdlib.h>
#include "AgregarEnemigoButton.h"

AgregarEnemigoButton::AgregarEnemigoButton(int horda,
                                           const std::string &enemigo,
                                           SDL_Texture *texture,
                                           MousePosition &mousePosition,
                                           Renderer &renderer, Editor &editor)
        : Button(0, 0, HORDA_MODIFY_QUANTITY_SIZE, HORDA_MODIFY_QUANTITY_SIZE,
                 texture, mousePosition, renderer), horda(horda),
          enemigo(enemigo), editor(editor) {}

void AgregarEnemigoButton::click() {
    editor.agregarEnemigo(horda, enemigo);
}

void AgregarEnemigoButton::draw(int number) {
    div_t division = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    button.x = HORDA_MODIFY_QUANTITY_SIZE;
    button.y =
            HORDA_MODIFY_QUANTITY_PADDING + division.quot * HORDA_TOTAL_HEIGHT;
    Button::draw(number);

}