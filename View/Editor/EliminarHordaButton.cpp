#include "EliminarHordaButton.h"

EliminarHordaButton::EliminarHordaButton(int horda, SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer,
                                         Editor &editor)
        : Button(200, 300 + 200 * horda, 200, 50, texture, mousePosition,
                 renderer),
          editor(editor), horda(horda) {}

void EliminarHordaButton::click() {
    editor.eliminarHorda(horda);
}
