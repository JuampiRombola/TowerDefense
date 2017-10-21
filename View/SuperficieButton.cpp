#include "SuperficieButton.h"
#include <iostream>

SuperficieButton::SuperficieButton(int number, const std::string&
                                   superficie, SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor) :
        Button(number*100, 0, 100, 100, texture, mousePosition, renderer),
        number(number), superficie(superficie), editor(editor) {}

SuperficieButton::~SuperficieButton() = default;

void SuperficieButton::click() {
    editor.setSuperficie(superficie);
}
