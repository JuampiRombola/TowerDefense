#include "EliminarEnemigoButton.h"

EliminarEnemigoButton::EliminarEnemigoButton(int horda,
                                             const std::string &enemigo,
                                             SDL_Texture *texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor)
        : Button(0, 250 + horda * 150, 200, 50, texture, mousePosition,
                 renderer), horda(horda), enemigo(enemigo), editor(editor) {}

void EliminarEnemigoButton::click() {
    editor.eliminarEnemigo(horda, enemigo);
}

EliminarEnemigoButton::~EliminarEnemigoButton() = default;
