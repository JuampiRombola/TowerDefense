#include "SpellButton.h"
#include "ViewConstants.h"

SpellButton::SpellButton(Window &w, int type, int &cmd,
                               SDL_Texture *texture,
                               MousePosition &mousePosition,
                               Renderer &renderer, int n)
        : type(type), command(cmd),
          Button(w.getWidth() - n*SPELL_BUTTON_WIDTH - n*PADDING_HUD,
                 w.getHeight() - SPELL_BUTTON_HEIGHT - PADDING_HUD,
                 SPELL_BUTTON_WIDTH, SPELL_BUTTON_HEIGHT,
                 texture, mousePosition, renderer) {}

void SpellButton::draw() {
    Button::draw(0);
}

void SpellButton::click() {
    command = type;
    printf("Casteo un spell  %d\n", type);
}