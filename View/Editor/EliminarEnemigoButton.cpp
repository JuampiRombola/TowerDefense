#include <iostream>
#include "EliminarEnemigoButton.h"

EliminarEnemigoButton::EliminarEnemigoButton(int id, int horda,
                                             const std::string &enemigo,
                                             SDL_Texture *texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor)
        : Button(id, 0, 300 + horda * 200, 50, 50, texture, mousePosition,
                 renderer), horda(horda), enemigo(enemigo), editor(editor) {}

void EliminarEnemigoButton::click() {
    editor.eliminarEnemigo(horda, enemigo);
}
