#include "GameButtons.h"

GameButtons::GameButtons(MousePosition &mousePosition, Renderer &renderer,
                         TextureLoader &textureLoader,
                         CommandDispatcher &dispatcher) : mousePosition(
        mousePosition), renderer(renderer), textureLoader(textureLoader),
        dispatcher(dispatcher) {}

GameButtons::~GameButtons() {
    for (auto &image : images)
        delete image;
}

void GameButtons::addTowerButtons() {
}