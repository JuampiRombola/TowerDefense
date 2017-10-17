#ifndef TOWERDEFENSE_MAPVIEW_H
#define TOWERDEFENSE_MAPVIEW_H

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "TextureLoader.h"
#include "../src/PathTile.h"
#include "../src/StructureTile.h"

class MapView {
private:
    int width;
    int height;
    Renderer *renderer;
    std::vector<PathTile*> *pathTiles;
    std::vector<StructureTile*> *structureTiles;
    SDL_Texture *tileTexture;
    SDL_Texture *pathTexture;
    SDL_Texture *structureTexture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

public:
    MapView(int width, int height, int env,
            Renderer *renderer,
            std::vector<PathTile*> *pTiles,
            std::vector<StructureTile*> *sTiles,
            TextureLoader *textures);
    ~MapView();
    void draw(Uint32 ticks);
};


#endif //TOWERDEFENSE_MAPVIEW_H
