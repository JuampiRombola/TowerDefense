#include "TextInput.h"

TextInput::TextInput(int id, int posX, int posY, int width, int height,
                     SDL_Texture *texture, MousePosition &mousePosition,
                     Renderer &renderer) : Button(id, posX, posY, width, height,
                                                  texture, mousePosition,
                                                  renderer),
                                           text("Hola Mundo") {}

void TextInput::draw() {
    //if (Button::isClicked()) {
    int xActual = button.x;
    for (char &caracter : text) {
        SDL_Rect src = {0, (caracter - 32) * 24, 14, 24};
        SDL_Rect dst = {xActual, button.y, 14, 24};
        renderer.copyEuclidean(texture, &src, &dst);
        xActual += 14;
    }
    //}
}

void TextInput::click() {}

TextInput::~TextInput() {}