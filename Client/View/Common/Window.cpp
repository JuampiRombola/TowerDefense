#include "Window.h"
#include "ViewError.h"

Window::Window(const std::string &title, int width, int height) :
        width(width), height(height) {
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED, // x position
                              SDL_WINDOWPOS_UNDEFINED, // y position
                              width, height,
                              SDL_WINDOW_FULLSCREEN_DESKTOP);   // Flag
    if (!window) throw ViewError("Create window error: %s", SDL_GetError());
    SDL_GetWindowSize(window, &this->width, &this->height);
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

SDL_Window *Window::getWindow() {
    return window;
}

void Window::showErrorMessage(const std::string &title, const std::string
&description) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(),
                             description.c_str(), window);
}
