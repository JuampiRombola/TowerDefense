#include "MousePosition.h"

MousePosition::MousePosition(int &x, int &y) : x(x), y(y), active(false) {}

MousePosition::~MousePosition() = default;

int MousePosition::getPosX() {
    return x;
}

int MousePosition::getPosY() {
    return y;
}

bool MousePosition::isActive() {
    return active;
}

void MousePosition::toggleActive() {
    active = !active;
}