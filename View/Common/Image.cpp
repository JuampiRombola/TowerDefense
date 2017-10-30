#include "Image.h"

Image::Image(int posX, int posY, int width, int height, SDL_Texture *texture,
             Renderer &renderer) : renderer(renderer), texture(texture),
                                   button(SDL_Rect{posX, posY, width,
                                                   height}) {}

void Image::draw() {
    renderer.copyEuclidean(texture, &button);
}
