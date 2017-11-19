#include "Text.h"

Text::Text(int posX, int posY, int width, int height,
                     SDL_Texture *texture,
                     Renderer &renderer) : Image(posX, posY, width, height,
                                                  texture, renderer),
                                           text("") {}

void Text::draw(int number, int padding) {
    int xActual = button.x;
    for (char &caracter : text) {
        SDL_Rect src = {0, (caracter - 32) * 24, 14, 24};
        SDL_Rect dst = {xActual, button.y, 14, 24};
        renderer.copyEuclidean(texture, &src, &dst);
        xActual += 14;
    }
}
