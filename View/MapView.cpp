#include "MapView.h"
#include <algorithm>

#define STRUCTURETILE 1
#define PATHTILE 2

#define TIME 180
#define NSPRITES 5

#define XSPRITESRCTILE 0
#define YSPRITESRCTILE 3385

#define XSPRITESRC 0
#define YSPRITESRC 0

#define WIDTHTILE 160
#define HEIGHTTILE 80

MapView::MapView(int width, int height, int env,
                 Renderer *renderer,
                 std::vector<PathTile*> *pTiles,
                 std::vector<SolidGroundTile*> *sTiles,
                 TextureLoader *textures) :
        width(width), height(height), renderer(renderer),
        pathTiles(pTiles), structureTiles(sTiles) {
    tileTexture = textures->getTexture(env);
    structureTexture = textures->getTexture(STRUCTURETILE);
    pathTexture = textures->getTexture(PATHTILE);
    srcRect.w = WIDTHTILE;
    srcRect.h = HEIGHTTILE;
    dstRect.w = WIDTHTILE;
    dstRect.h = HEIGHTTILE;
}

MapView::~MapView() {

}

void MapView::draw(Uint32 ticks) {
    Uint32 tick = (ticks / TIME) % NSPRITES;
    srcRect.x = tick * (XSPRITESRCTILE + WIDTHTILE);
    srcRect.y = YSPRITESRCTILE;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            dstRect.x = x; // Paso x en coord cartesianas
            dstRect.y = y; // Paso y en coord cartesianas
            // Dentro de render->copy() se cambia a coord isometricas
            renderer->copy(tileTexture, &srcRect, &dstRect);
        }
    }

    srcRect.x = XSPRITESRC;
    srcRect.y = YSPRITESRC;
    for (unsigned int i = 0; i < (*pathTiles).size(); ++i) {
        dstRect.x = ((*pathTiles)[i])->GetXPos(); // Paso x en coord cartesianas
        dstRect.y = ((*pathTiles)[i])->GetYPos(); // Paso y en coord cartesianas
        // Dentro de render->copy() se cambia a coord isometricas
        renderer->copy(pathTexture, &srcRect, &dstRect);
    }

    srcRect.x = XSPRITESRC;
    srcRect.y = YSPRITESRC;
    for (unsigned int i = 0; i < (*structureTiles).size(); ++i) {
        dstRect.x = ((*structureTiles)[i])->GetXPos(); // Paso x en coord cartesianas
        dstRect.y = ((*structureTiles)[i])->GetYPos(); // Paso y en coord cartesianas
        // Dentro de render->copy() se cambia a coord isometricas
        renderer->copy(structureTexture, &srcRect, &dstRect);
    }
}
