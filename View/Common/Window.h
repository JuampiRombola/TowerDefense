#ifndef TOWERDEFENSE_WINDOW_H
#define TOWERDEFENSE_WINDOW_H

#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    SDL_Window *window;
    int width;
    int height;

public:
    Window(const std::string &title, int width, int height);
    ~Window();
    int getWidth();
    int getHeight();
    SDL_Window* getWindow();
};


#endif //TOWERDEFENSE_WINDOW_H