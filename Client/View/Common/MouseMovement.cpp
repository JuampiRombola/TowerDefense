#include "MouseMovement.h"

#define MOUSE_TOLERANCE 5

MouseMovement::MouseMovement(Renderer &r) : renderer(r), x(100), y(100) {}

void MouseMovement::doMovement() {
    if (windowID != renderer.getWindowID()) return;
    if (x < MOUSE_TOLERANCE) {
        renderer.updateCamera(-2, 0);
    }
    if (x > (renderer.getWindowWidth()-MOUSE_TOLERANCE)) {
        renderer.updateCamera(2, 0);
    }
    if (y < MOUSE_TOLERANCE) {
        renderer.updateCamera(0, -2);
    }
    if (y > (renderer.getWindowHeight()-MOUSE_TOLERANCE)) {
        renderer.updateCamera(0, 2);
    }
}

void MouseMovement::entryMovement(int x, int y, Uint32 windowID) {
    this->x = x;
    this->y = y;
    this->windowID = windowID;
}
