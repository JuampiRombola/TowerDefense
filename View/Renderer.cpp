#include "Renderer.h"

#define HEIGHTTL 80
#define MIDWIDTHTILE 80

Renderer::Renderer(Window *window, int mapWidth) :
        mapWidth(mapWidth * MIDWIDTHTILE), // Para hacer el calculo de coord isometricas
        renderer(SDL_CreateRenderer(window->getWindow(), -1, 0)),
        x(window->get_width()), y(window->get_height()) {}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst) {
    x = dst->x;
    y = dst->y;
    dst->x = cartesianToIsometricX(x, y);
    dst->y = cartesianToIsometricY(x, y);
    SDL_RenderCopy(renderer, texture, src, dst);
}

void Renderer::clearRender() {
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::updateCamera(int x, int y) {
    this->x += x;
    this->y += y;
}

SDL_Renderer *Renderer::getRenderer() {
    return renderer;
}

int Renderer::cartesianToIsometricX(int x, int y) {
    return ((x  - y) * MIDWIDTHTILE) + mapWidth - MIDWIDTHTILE;
}

int Renderer::cartesianToIsometricY(int x, int y) {
    return ((x  + y) * HEIGHTTL / 2);
}
