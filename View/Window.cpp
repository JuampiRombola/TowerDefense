#include "Window.h"
#include "ViewError.h"

Window::Window(const std::string &title, int width, int height) :
        width(width), height(height) {
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, // x position
                              SDL_WINDOWPOS_UNDEFINED, // y position
                              width, height,
                              SDL_WINDOW_RESIZABLE);   // Flag
    if (!window) throw ViewError("Create window error: %s", SDL_GetError());
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

int Window::get_width() {
    return width;
}

int Window::get_height() {
    return height;
}

SDL_Window *Window::getWindow() {
    return window;
}
