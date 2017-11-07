#include "ContadorEnemigosInput.h"

ContadorEnemigosInput::ContadorEnemigosInput(int horda, std::string enemigo,
                                             SDL_Texture *texture,
                                             Renderer &renderer, Editor &editor)
        : Text(0, 0, HORDA_QUANTITY_HEIGHT, HORDA_QUANTITY_WIDTH, texture,
               renderer), horda(horda), enemigo(std::move(enemigo)),
          editor(editor) {}

void ContadorEnemigosInput::draw(int number) {
    button.x = 0;
    button.y = HORDA_QUANTITY_PADDING +
               (number - TOTAL_MAIN_BUTTONS - HORDA_TOTAL_ENEMIES -
                HORDA_TOTAL_MODIFY_QUANTITY) * HORDA_TOTAL_HEIGHT /
               (HORDA_TOTAL_BUTTONS);
    this->text = std::to_string(
            editor.getCantidadEnemigosEnHorda(enemigo, horda));
    Text::draw(number);
}

