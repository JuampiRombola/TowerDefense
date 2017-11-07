#include "ContadorEnemigosInput.h"

ContadorEnemigosInput::ContadorEnemigosInput(int horda, std::string enemigo, SDL_Texture *texture,
                                             Renderer &renderer, Editor
                                             &editor) :
        Text(0, 450 + horda * 200, 28, 100, texture, renderer), enemigo
        (std::move(enemigo)), editor(editor) {}

void ContadorEnemigosInput::draw() {
    this->text = std::to_string(editor.getCantidadEnemigosEnHorda(enemigo,
                                                                  horda));
    Text::draw(0);
}