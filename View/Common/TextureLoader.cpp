#include <string>
#include "TextureLoader.h"
#include "ViewError.h"
#include "SpriteNamesConfig.h"

#define CONFIG_PATH "../View/spritesConfig.yaml"
#define RESOURCESPATH "../Resources/"
#define PNGFORMAT ".png"

#define GAME_MODE 0
#define EDITOR_MODE 1

TextureLoader::TextureLoader(SDL_Renderer *renderer, int mode) :
        cfg(YAML::LoadFile(CONFIG_PATH)) {
    int totalGame = TOTAL;
    int totalEditor = TOTAL_EDITOR;
    if (mode == GAME_MODE)
        totalEditor = 0;
    if (mode == EDITOR_MODE)
        totalGame = PORTALSALIDA + 1;

    IMG_Init(IMG_INIT_PNG);
    for (int i = 0; i < totalGame; ++i) {
        SDL_Surface *im = IMG_Load((RESOURCESPATH
                                    + std::to_string(i)
                                    + PNGFORMAT).c_str());
        images.push_back(im);
        SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, im);
        if (!tx) throw ViewError("Load textures error: %s", SDL_GetError());
        textures[i] = tx;
    }

    for (int i = 100; i < totalEditor; ++i) {
        SDL_Surface *im = IMG_Load((RESOURCESPATH
                                    + std::to_string(i)
                                    + PNGFORMAT).c_str());
        images.push_back(im);
        SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, im);
        if (!tx) throw ViewError("Load textures error: %s", SDL_GetError());
        textures[i] = tx;
    }
}

TextureLoader::~TextureLoader() {
    for (auto &item : textures)
        SDL_DestroyTexture(item.second);
    for (int i = 0; i < images.size(); ++i)
        SDL_FreeSurface(images[i]);
    IMG_Quit();
}

SDL_Texture *TextureLoader::getTexture(int pos) {
    return textures[pos];
}

const YAML::Node TextureLoader::getConfig(int key) {
    return cfg[this->intToStringKey(key)];
}

std::string TextureLoader::intToStringKey(int key) {
    if (key == ABOMINABLE)
        return "ABOMINABLE";
    if (key == HALCONSANGRIENTO)
        return "HALCONSANGRIENTO";
}
