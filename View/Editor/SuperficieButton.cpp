#include "SuperficieButton.h"

SuperficieButton::SuperficieButton(int id, int number, const int
                                   superficie, SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor) :
        Button(id, number*100, 0, 100, 100, texture, mousePosition, renderer),
        number(number), superficie(superficie), editor(editor) {}

SuperficieButton::~SuperficieButton() = default;

void SuperficieButton::click() {
    editor.setSuperficie(superficie);
}