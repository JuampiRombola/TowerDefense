#include "HudView.h"

HudView::HudView(Window &w, TextureLoader &tl, Renderer &r,
                 CommandDispatcher &cd) :
        textureLoader(tl), renderer(r), dispatcher(cd),
        mouse_y(-1), mousePosition(mouse_x, mouse_y),
        buttons(w, mousePosition, r, tl, cd) {}

void HudView::getMouseState() {
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mousePosition.activate();
}

void HudView::getFingerState(SDL_Event &event) {
    mouse_x = static_cast<int>(event.tfinger.x);
    mouse_y = static_cast<int>(event.tfinger.y);
    mousePosition.activate();
}

void HudView::doMouseAction() {
    if (!mousePosition.isActive()) return;

    if (!buttons.isAnyClicked() && currentCommand != -1) {
        int tileX = renderer.pixelToCartesianX(mouse_x, mouse_y);
        int tileY = renderer.pixelToCartesianY(mouse_x, mouse_y);
        this->sendCommand(tileX, tileY);
        mousePosition.deactivate();
        currentCommand = -1;
    }
}

void HudView::sendCommand(int x, int y) {
    printf("Crear torre elemento %d en la posicion (%d, %d)\n",
           currentCommand, x, y);
}

void HudView::draw() {
    buttons.draw();
}

void HudView::addElementalButtons(int key) {
    buttons.addTowerButtons(key, currentCommand);
}

