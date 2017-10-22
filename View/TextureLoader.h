#ifndef TOWERDEFENSE_TEXTURELOADER_H
#define TOWERDEFENSE_TEXTURELOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class TextureLoader {
private:
    std::vector<SDL_Surface *> images;
    std::vector<SDL_Texture *> textures;

public:
    explicit TextureLoader(SDL_Renderer *renderer);
    ~TextureLoader();
    SDL_Texture *getTexture(int pos);
};


#endif //TOWERDEFENSE_TEXTURELOADER_H
