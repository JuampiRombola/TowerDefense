#include "Renderer.h"

#define HEIGHTFACTOR 80
#define WIDTHFACTOR 80

#define PADDING 150
#define ZOOMINITIAL 1

#define MOVECAMERA 10

Renderer::Renderer(Window &window, int mapWidth, int mapHeight) :
        mapWidth(mapWidth * WIDTHFACTOR * 2),
        mapHeight(mapHeight * HEIGHTFACTOR),
        cameraX(this->mapWidth/4), cameraY(this->mapHeight/4),
        paddingWidth(mapWidth * WIDTHFACTOR + PADDING),
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
                    const SDL_Rect *src, SDL_Rect *dst) {
    int x = dst->x;
    int y = dst->y;
    dst->x = cartesianToIsometricX(x, y) - cameraX;
    dst->y = cartesianToIsometricY(x, y) - cameraY;
    if (!isOnCamera(dst->x, dst->y)) return;
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
    if (cameraX > (mapWidth * zoom - windowWidth + 2 * PADDING * zoom))
        cameraX = mapWidth * zoom - windowWidth + 2 * PADDING * zoom;

    this->cameraY += (y * factor);
    if (cameraY < 0) cameraY = 0;
    if (cameraY > (mapHeight * zoom - windowHeight + 2 * PADDING))
        cameraY = mapHeight * zoom - windowHeight + 2 * PADDING;
}

SDL_Renderer *Renderer::getRenderer() {
    return renderer;
}

int Renderer::cartesianToIsometricX(int x, int y) {
    return (((x  - y) * WIDTHFACTOR) + paddingWidth - WIDTHFACTOR) * zoom;
}

int Renderer::cartesianToIsometricY(int x, int y) {
    return ((x  + y) * HEIGHTFACTOR * zoom / 2) + paddingHeight;
}

void Renderer::zoomIn() {
    if (zoom < 5) zoom += 1;
}

void Renderer::zoomOut() {
    if (zoom > 1) zoom -= 1;
}

bool Renderer::isOnCamera(int x, int y) {
    return ((x >= -WIDTHFACTOR * 2 * zoom) && (y >= -HEIGHTFACTOR * zoom) &&
            (x <= windowWidth) && (y <= windowHeight));
}
