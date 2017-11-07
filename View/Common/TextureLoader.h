#ifndef TOWERDEFENSE_TEXTURELOADER_H
#define TOWERDEFENSE_TEXTURELOADER_H

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include <string>

class TextureLoader {
private:
    std::vector<SDL_Surface *> images;
    std::map<int, SDL_Texture*> textures;
    const YAML::Node cfg;

public:
    TextureLoader(SDL_Renderer *renderer, int mode);
    ~TextureLoader();
    SDL_Texture *getTexture(int pos);
    const YAML::Node getConfig(int key);

private:
    std::string intToStringKey(int key);
};


#endif //TOWERDEFENSE_TEXTURELOADER_H
