#include "MousePosition.h"

MousePosition::MousePosition(int &x, int &y, bool &active) : x(x), y(y), active
        (active) {}

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