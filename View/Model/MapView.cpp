#include "MapView.h"
#include "../Common/SpriteNamesConfig.h"

#define PATHTILE 1

MapView::MapView(int width, int height, int env,
                 Renderer &renderer, TextureLoader &textures) :
        width(width), height(height),
        envTile(textures.getTexture(env), renderer),
        pathTile(textures.getTexture(env + PATHTILE), renderer),
        structureTile(textures.getTexture(TIERRAFIRME), renderer),
        textures(textures), renderer(renderer) {
    selectBackgroundColor(renderer, env);
    envTile.setSourceRect(0, 0, 128, 96);
    envTile.setDestRect(0, 0, 160, 120);
    pathTile.setSourceRect(0, 0, 128, 64);
    pathTile.setDestRect(0, 0, 160, 80);
    structureTile.setSourceRect(0, 0, 511, 256);
    structureTile.setDestRect(0, 0, 160, 80);
}

MapView::~MapView() {}

void MapView::draw(Uint32 ticks) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            envTile.setDestXY(x, y);
            envTile.draw();
        }
    }
    for (auto &pTile : pathTiles) {
        pathTile.setDestXY(pTile.first, pTile.second);
        pathTile.draw();
    }
    for (auto &sTile : structureTiles) {
        structureTile.setDestXY(sTile.first, sTile.second);
        structureTile.draw();
    }
}

void MapView::addPathTile(int x, int y) {
    pathTiles.emplace_back(x, y);
}

void MapView::addStructureTile(int x, int y) {
    structureTiles.emplace_back(x, y);
}

void MapView::selectBackgroundColor(Renderer &renderer, int environment) {
    if (environment == PRADERA)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 52, 73, 94, 255);
    if (environment == VOLCAN)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 52, 73, 94, 255);
    if (environment == GELIDO)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 52, 73, 94, 255);
    if (environment == DESIERTO)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 52, 73, 94, 255);
}

void MapView::setEnvTile(int env) {
    envTile.setTexture(textures.getTexture(env));
    selectBackgroundColor(renderer, env);
}
