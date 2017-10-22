#ifndef TOWERDEFENSE_MAPVIEW_H
#define TOWERDEFENSE_MAPVIEW_H

#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Renderer.h"
#include "TextureLoader.h"
<<<<<<< HEAD
=======
#include "../src/PathTile.h"
#include "../src/SolidGroundTile.h"
>>>>>>> a6e3d36613f80f66fc031a8349f388a120cee68a

class MapView {
private:
    int width;
    int height;
<<<<<<< HEAD
    std::vector<std::pair<int, int>> pathTiles;
    std::vector<std::pair<int, int>> structureTiles;
    Sprite envTile;
    Sprite pathTile;
    Sprite structureTile;

public:
    MapView(int width, int height, int env,
            Renderer &renderer, TextureLoader &textures);
=======
    Renderer *renderer;
    std::vector<PathTile*> *pathTiles;
    std::vector<SolidGroundTile*> *structureTiles;
    SDL_Texture *tileTexture;
    SDL_Texture *pathTexture;
    SDL_Texture *structureTexture;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

public:
    MapView(int width, int height, int env,
            Renderer *renderer,
            std::vector<PathTile*> *pTiles,
            std::vector<SolidGroundTile*> *sTiles,
            TextureLoader *textures);
>>>>>>> a6e3d36613f80f66fc031a8349f388a120cee68a
    ~MapView();
    void draw(Uint32 ticks);
    void addPathTile(int x, int y);
    void addStructureTile(int x, int y);
    void selectBackgroundColor(Renderer &renderer, int environment);
};


#endif //TOWERDEFENSE_MAPVIEW_H
