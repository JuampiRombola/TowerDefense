#include <iostream>
#include <cmath>
#include "Renderer.h"

#define HEIGHTFACTOR 80
#define WIDTHFACTOR 80

#define PADDING 400
#define ZOOMINITIAL 1

#define MOVECAMERA 10
#define TOLERANCE 380

Renderer::Renderer(Window &window, int mapWidth, int mapHeight) :
        window(window),
        mapWidth(mapWidth*WIDTHFACTOR + mapHeight*WIDTHFACTOR - WIDTHFACTOR),
        mapHeight(this->mapWidth / 2),
        cameraX(0), cameraY(this->mapHeight/4),
        paddingWidth(mapHeight * WIDTHFACTOR + PADDING),
        paddingHeight(PADDING),
        zoom(ZOOMINITIAL),
        renderer(SDL_CreateRenderer(window.getWindow(), -1, 0)),
        windowWidth(window.getWidth()), windowHeight(window.getHeight()) {
    if (!renderer)
        throw ViewError("Create renderer error: %s", SDL_GetError());
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::copy(SDL_Texture *texture,
                    const SDL_Rect *src, SDL_Rect *dst,
                    int offsetX, int offsetY) {
    int x = dst->x;
    int y = dst->y;
    dst->x = (cartesianToIsometricX(x, y) - offsetX - cameraX) * zoom;
    dst->y = (cartesianToIsometricY(x, y) - offsetY - cameraY) * zoom;
    if (!isOnCamera(dst->x, dst->y)) {
        dst->x = x;
        dst->y = y;
        return;
    }
    int dstW = dst->w;
    int dstH = dst->h;
    dst->w *= zoom;
    dst->h *= zoom;
    SDL_RenderCopy(renderer, texture, src, dst);
    dst->x = x;
    dst->y = y;
    dst->w = dstW;
    dst->h = dstH;
}

void Renderer::copyEuclidean(SDL_Texture *texture, SDL_Rect *src, SDL_Rect
*dst) {
    SDL_RenderCopy(renderer, texture, src, dst);
}

void Renderer::copyEuclidean(SDL_Texture *texture, SDL_Rect *dst) {
    SDL_RenderCopy(renderer, texture, NULL, dst);
}

void Renderer::clearRender() {
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::updateCamera(int x, int y) {
    int factor = MOVECAMERA * zoom;

    this->cameraX += (x * factor);
    if (cameraX < 0) cameraX = 0;
    if (cameraX > (ceil(zoom) * mapWidth + 2*PADDING - windowWidth))
        cameraX = ceil(zoom) * mapWidth + 2*PADDING - windowWidth;

    this->cameraY += (y * factor);
    if (cameraY < 0) cameraY = 0;
    if (cameraY > (ceil(zoom) * mapHeight + 2*PADDING - windowHeight))
        cameraY = ceil(zoom) * mapHeight + 2*PADDING - windowHeight;
}

SDL_Renderer *Renderer::getRenderer() {
    return renderer;
}

int Renderer::cartesianToIsometricX(int x, int y) {
    return (((x  - y) * WIDTHFACTOR) + paddingWidth);
}

int Renderer::cartesianToIsometricY(int x, int y) {
    return ((x  + y) * HEIGHTFACTOR / 2) + paddingHeight;
}

void Renderer::zoomIn() {
    if (zoom < 5 && zoom >= 1) {
        zoom += 1;
        cameraX += (windowWidth / 2 / zoom);
        cameraY += (windowHeight / 2 / zoom);
    }

    if (zoom == 0.75)
        zoom = 1;

    if (zoom == 0.5)
        zoom = 0.75;
}

void Renderer::zoomOut() {
    if (zoom == 0.75)
        zoom = 0.5;

    if (zoom == 1)
        zoom = 0.75;

    if (zoom > 1) {
        cameraX -= (windowWidth / 2 / zoom);
        cameraY -= (windowHeight / 2 / zoom);
        zoom -= 1;
    }
}

bool Renderer::isOnCamera(int x, int y) {
    return ((x >= -(WIDTHFACTOR + TOLERANCE) * zoom) &&
            (y >= -(HEIGHTFACTOR + TOLERANCE) * zoom) &&
            (x <= windowWidth) && (y <= windowHeight));
}

int Renderer::pixelToCartesianX(int x, int y) {
    double result = ((x/zoom + cameraX - paddingWidth - WIDTHFACTOR)
                     / static_cast<double>(WIDTHFACTOR) +
                    (y/zoom + cameraY - paddingHeight)
                     / static_cast<double>(HEIGHTFACTOR / 2)) / 2;
    if (result < 0) return -1;
    return static_cast<int>(result);
}

int Renderer::pixelToCartesianY(int x, int y) {
    double result = ((y / zoom + cameraY - paddingHeight)
                     / static_cast<double>(HEIGHTFACTOR / 2) -
                     (x/zoom +cameraX - paddingWidth - WIDTHFACTOR)
                     / static_cast<double>(WIDTHFACTOR)) / 2;
    if (result < 0) return -1;
    return static_cast<int>(result);
}

void Renderer::setMapWidth(int mapH, int newW) {
    mapWidth = newW*WIDTHFACTOR + mapH*WIDTHFACTOR - WIDTHFACTOR;
    mapHeight = mapWidth / 2;
}

void Renderer::setMapHeight(int mapW, int mapH, int newH) {
    mapWidth = mapW*WIDTHFACTOR + newH*WIDTHFACTOR - WIDTHFACTOR;
    mapHeight = mapWidth / 2;
    paddingWidth = newH * WIDTHFACTOR + PADDING;
    cameraX += (newH - mapH) * WIDTHFACTOR;
}

int Renderer::getWindowWidth() {
    return window.getWidth();
}

int Renderer::getWindowHeight() {
    return window.getHeight();
}

Uint32 Renderer::getWindowID() {
    return window.getID();
}
