#include "EliminarTerrenoButton.h"

EliminarTerrenoButton::EliminarTerrenoButton(SDL_Texture *texture, MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor) : Button(
        ELIMINAR_TERRENO_BUTTON_X, ELIMINAR_TERRENO_BUTTON_Y, ELIMINAR_TERRENO_BUTTON_WIDTH,
        ELIMINAR_TERRENO_BUTTON_HEIGHT, texture, mousePosition, renderer), editor(editor) {}

void EliminarTerrenoButton::click() {
    editor.waitForDeleteTerrainTile();
}