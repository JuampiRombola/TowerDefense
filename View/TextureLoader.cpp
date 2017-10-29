#include <string>
#include "TextureLoader.h"
#include "ViewError.h"
#include "SpriteNamesConfig.h"

#define RESOURCESPATH "../Resources/"
#define PNGFORMAT ".png"

TextureLoader::TextureLoader(SDL_Renderer *renderer) {
    IMG_Init(IMG_INIT_PNG);
    for (int i = 0; i < TOTAL; ++i) {
        SDL_Surface *im = IMG_Load((RESOURCESPATH
                                    + std::to_string(i)
                                    + PNGFORMAT).c_str());
        images.push_back(im);
        SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, im);
        if (!tx) throw ViewError("Load textures error: %s", SDL_GetError());
        textures.push_back(tx);
    }

    for (int i = 100; i < TOTAL_EDITOR; ++i) {
        SDL_Surface *im = IMG_Load((RESOURCESPATH
                                    + std::to_string(i)
                                    + PNGFORMAT).c_str());
        images.push_back(im);
        SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, im);
        if (!tx) throw ViewError("Load textures error: %s", SDL_GetError());
        textures.push_back(tx);
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
