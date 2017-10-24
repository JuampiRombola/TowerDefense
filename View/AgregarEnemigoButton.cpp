#include "AgregarEnemigoButton.h"


AgregarEnemigoButton::AgregarEnemigoButton(int horda,
                                           const std::string &enemigo,
                                           SDL_Texture *texture,
                                           MousePosition &mousePosition,
                                           Renderer &renderer, Editor &editor)
        : Button(0, 200 + horda * 150, 200, 50, texture, mousePosition,
                 renderer), horda(horda), enemigo(enemigo), editor(editor) {}

void AgregarEnemigoButton::click() {
    editor.agregarEnemigo(horda, enemigo);
}

AgregarEnemigoButton::~AgregarEnemigoButton() = default;