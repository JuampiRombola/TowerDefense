#include "SpellButton.h"
#include "ViewConstants.h"

SpellButton::SpellButton(Window &w, int type, int &cmd,
                         SDL_Texture *texture,
                         SDL_Texture *transp,
                         MousePosition &mousePosition,
                         Renderer &renderer, int n)
        : type(type), command(cmd),
          Button(w.getWidth() - n*SPELL_BUTTON_WIDTH - n*PADDING_HUD,
                 w.getHeight() - SPELL_BUTTON_HEIGHT - PADDING_HUD,
                 SPELL_BUTTON_WIDTH, SPELL_BUTTON_HEIGHT,
                 texture, mousePosition, renderer),
          transparency(button.x, button.y, button.w, button.h,
                       transp, renderer) {}

void SpellButton::draw(int number) {
    Button::draw(0);
    if (!this->wasLastClick())
        transparency.draw(0);
}

void SpellButton::click() {
    command = type;
    printf("Clickeo un spellbutton  %d\n", type);
}