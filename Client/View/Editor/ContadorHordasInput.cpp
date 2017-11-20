#include "ContadorHordasInput.h"

ContadorHordasInput::ContadorHordasInput(int horda,
                                         SDL_Texture *texture,
                                         Renderer &renderer)
        : Text(0, 0, HORDA_QUANTITY_HEIGHT, HORDA_QUANTITY_WIDTH, texture,
               renderer), horda(horda) {}

void ContadorHordasInput::draw(int number, int padding) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    if (hordaNro.quot < padding)
        return;
    button.x = 0;
    button.y = HORDA_QUANTITY_PADDING +
               (hordaNro.quot - padding) * HORDA_TOTAL_HEIGHT;
    this->text = std::to_string(hordaNro.quot + 1);
    Text::draw(number, 0);
}

bool ContadorHordasInput::belongsToHorda(int hordaNro) {
    return horda == hordaNro;
}