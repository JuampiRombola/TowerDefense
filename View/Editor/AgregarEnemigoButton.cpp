#include "AgregarEnemigoButton.h"

AgregarEnemigoButton::AgregarEnemigoButton(int id, int horda,
                                           const std::string &enemigo,
                                           SDL_Texture *texture,
                                           MousePosition &mousePosition,
                                           Renderer &renderer, Editor &editor)
        : Button(id, 50, 300 + horda * 200, 50, 50, texture, mousePosition,
                 renderer), horda(horda), enemigo(enemigo), editor(editor) {}

void AgregarEnemigoButton::click() {
    editor.agregarEnemigo(horda, enemigo);
}

AgregarEnemigoButton::~AgregarEnemigoButton() = default;