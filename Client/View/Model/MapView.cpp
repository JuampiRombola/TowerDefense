#include <cmath>
#include "MapView.h"
#include "../Common/SpriteNamesConfig.h"

#define PATHTILE 1

#define STRUCTURE_COLUMNS 2
#define STRUCTURE_ROWS 1
#define STRUCTURE_TPS 350

#define SPRITE_TILE_W 128
#define SPRITE_TILE_H 64
#define SPRITE_TILE_DEEP_H 96
#define STRUCTURE_W 511
#define STRUCTURE_H 256

#define TILE_WIDTH 160
#define TILE_HEIGHT 80
#define TILE_HEIGHT_DEEP 120

MapView::MapView(int width, int height, int env,
                 Renderer &renderer, TextureLoader &textures) :
        width(width), height(height),
        envTile(textures.getTexture(env), renderer),
        pathTile(textures.getTexture(env + PATHTILE), renderer),
        structureTile(textures.getTexture(TIERRAFIRME), renderer,
                      STRUCTURE_W, STRUCTURE_H, 0, 0,
                      STRUCTURE_COLUMNS, STRUCTURE_ROWS),
        textures(textures), renderer(renderer) {
    selectBackgroundColor(renderer, env);
    envTile.setSourceRect(0, 0, SPRITE_TILE_W, SPRITE_TILE_DEEP_H);
    envTile.setDestRect(0, 0, TILE_WIDTH, TILE_HEIGHT_DEEP);
    pathTile.setSourceRect(0, 0, SPRITE_TILE_W, SPRITE_TILE_H);
    pathTile.setDestRect(0, 0, TILE_WIDTH, TILE_HEIGHT);
    structureTile.setDestRect(0, 0, TILE_WIDTH, TILE_HEIGHT);
    structureTile.setTimePerSprite(STRUCTURE_TPS);
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
        structureTile.nextAndDraw(ticks);
    }
}

void MapView::addPathTile(int x, int y) {
    pathTiles.emplace_back(x, y);
}

void MapView::deletePathTile(int x, int y) {
    for (auto it = pathTiles.begin(); it != pathTiles.end();) {
        if ((*it).first == x && (*it).second == y)
            it = pathTiles.erase(it);
        else
            ++it;
    }
}

void MapView::addStructureTile(int x, int y) {
    structureTiles.emplace_back(x, y);
}

void MapView::deleteStructureTile(int x, int y) {
    for (auto it = structureTiles.begin(); it != structureTiles.end();) {
        if ((*it).first == x && (*it).second == y)
            it = structureTiles.erase(it);
        else
            ++it;
    }
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
    pathTile.setTexture(textures.getTexture(env + PATHTILE));
    selectBackgroundColor(renderer, env);
}

int MapView::getTileXFromPixel(int x, int y) {
    return renderer.pixelToCartesianX(x, y);
}

int MapView::getTileYFromPixel(int x, int y) {
    return renderer.pixelToCartesianY(x, y);
}

bool MapView::isValidTile(int x, int y) {
    return (x >= 0 && x < width) && (y >= 0 && y < height);
}

void MapView::setWidth(int newWidth) {
    if (newWidth < width) {
        for (auto it = pathTiles.begin(); it != pathTiles.end();) {
            if ((*it).first >= newWidth)
                pathTiles.erase(it);
            else
                ++it;
        }
        for (auto it = structureTiles.begin(); it != structureTiles.end();) {
            if ((*it).first >= newWidth)
                structureTiles.erase(it);
            else
                ++it;
        }
    }
    width = newWidth;
    renderer.setMapWidth(width, height);
}

int MapView::getWidth() {
    return width;
}

void MapView::setHeight(int newHeight) {
    if (newHeight < height) {
        for (auto it = pathTiles.begin(); it != pathTiles.end();) {
            if ((*it).second >= newHeight)
                pathTiles.erase(it);
            else
                ++it;
        }

        for (auto it = structureTiles.begin(); it != structureTiles.end();) {
            if ((*it).second >= newHeight)
                structureTiles.erase(it);
            else
                ++it;
        }
    }
    renderer.setMapHeight(width, height,newHeight);
    height = newHeight;
}

int MapView::getHeight() {
    return height;
}

std::set<std::pair<int, int>> MapView::getPathsAsSet() {
    std::set<std::pair<int, int>> pathSet;
    for (auto& pathTile : pathTiles) {
        pathSet.emplace(pathTile.first, pathTile.second);
    }
    return pathSet;
}

std::set<std::pair<int, int>> MapView::getStructureTilesAsSet() {
    std::set<std::pair<int, int>> structureTileSet;
    for (auto& structureTile : structureTiles) {
        structureTileSet.emplace(structureTile.first, structureTile.second);
    }
    return structureTileSet;
}