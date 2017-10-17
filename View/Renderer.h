#ifndef TOWERDEFENSE_RENDERER_H
#define TOWERDEFENSE_RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "ViewError.h"

class Renderer {
private:
    SDL_Renderer *renderer;
    int x; // x superior mostrado
    int y; // y superior mostrado
    int mapWidth;

public:
    Renderer(Window *window, int mapWidth);
    ~Renderer();
    void copy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst);
    void clearRender();
    void present();
    void updateCamera(int x, int y);
    int cartesianToIsometricX(int x, int y);
    int cartesianToIsometricY(int x, int y);
    SDL_Renderer* getRenderer();
};


#endif //TOWERDEFENSE_RENDERER_H
