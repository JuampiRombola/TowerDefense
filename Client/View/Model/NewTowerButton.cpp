#include "NewTowerButton.h"

NewTowerButton::NewTowerButton(Window &w, int element, int &cmd,
                               SDL_Texture *texture,
                               MousePosition &mousePosition,
                               Renderer &renderer, int n)
        : element(element), command(cmd),
          Button(w.getWidth() - n*TOWER_BUTTON_WIDTH - n*PADDING_HUD,
                 w.getHeight() - TOWER_BUTTON_HEIGHT - SPELL_BUTTON_HEIGHT
                 - 2*PADDING_HUD, TOWER_BUTTON_WIDTH, TOWER_BUTTON_HEIGHT,
                 texture, mousePosition, renderer) {}

void NewTowerButton::draw() {
    Button::draw(0);
}

void NewTowerButton::click() {
    command = element;
    printf("Hice click en el boton de la torre de elemento %d\n", element);
}
