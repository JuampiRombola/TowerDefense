#include <string>
#include "TextureLoader.h"

TextureLoader::TextureLoader(SDL_Renderer *renderer) {
    IMG_Init(IMG_INIT_PNG);
    for (int i = 0; i < TOTAL; ++i) {
        SDL_Surface *im = IMG_Load(("../Resources/"
                                    + std::to_string(i)
                                    + ".png").c_str());
        images.push_back(im);
        SDL_SetColorKey(im, SDL_TRUE, SDL_MapRGB(im->format, 255, 0,255));
        textures.push_back(SDL_CreateTextureFromSurface(renderer, im));
    }
}

TextureLoader::~TextureLoader() {
    for (int i = 0; i < TOTAL; ++i) {
        SDL_DestroyTexture(textures[i]);
        SDL_FreeSurface(images[i]);
    }
    IMG_Quit();
}

SDL_Texture *TextureLoader::getTexture(int pos) {
    return textures[pos];
}
