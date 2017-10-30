#ifndef TOWERDEFENSE_MAPVIEW_H
#define TOWERDEFENSE_MAPVIEW_H

#include <SDL2/SDL.h>
#include "../Common/Sprite.h"
#include "../Common/Renderer.h"
#include "../Common/TextureLoader.h"

class MapView {
private:
    int width;
    int height;
    std::vector<std::pair<int, int>> pathTiles;
    std::vector<std::pair<int, int>> structureTiles;
    Sprite envTile;
    Sprite pathTile;
    Sprite structureTile;
    TextureLoader& textures;
    Renderer& renderer;

public:
    MapView(int width, int height, int env,
            Renderer &renderer, TextureLoader &textures);
    ~MapView();
    void draw(Uint32 ticks);
    void addPathTile(int x, int y);
    void addStructureTile(int x, int y);
    void selectBackgroundColor(Renderer &renderer, int environment);
    void setEnvTile(int env);
};


#endif //TOWERDEFENSE_MAPVIEW_H
