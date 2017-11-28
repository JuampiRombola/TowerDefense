#include "SuperficieButton.h"

SuperficieButton::SuperficieButton(const int superficie,
                                   SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor) :
        Button(SUPERFICIE_BUTTON_WIDTH, SUPERFICIE_BUTTON_Y,
               SUPERFICIE_BUTTON_WIDTH, SUPERFICIE_BUTTON_HEIGHT,
               texture, mousePosition, renderer),
        superficie(superficie), editor(editor) {}

void SuperficieButton::click() {
    editor.setSuperficie(superficie);
}

void SuperficieButton::draw(int number, int padding) {
    button.x = number * SUPERFICIE_BUTTON_WIDTH + SUPERFICIE_BUTTON_X;
    Button::draw(number, 0);
}

