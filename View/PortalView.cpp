#include <iostream>
#include "PortalView.h"

#define PORTALW 138
#define PORTALH 181

#define PORTALANIMDESPL 40

#define PORTALN 30

PortalView::PortalView(int key, TextureLoader &textures, Renderer &renderer) :
        View(key, textures, renderer) {
    sprite.setSourceRect(0, 0, PORTALW, PORTALH);
    sprite.setDestRect(x, y, PORTALW, PORTALH);
    sprite.setLeftBotXY(0, 0);
}

PortalView::~PortalView() {}

void PortalView::draw(Uint32 ticks) {
    sprite.setSourceXY(0, 0);
    sprite.setLeftBotXY(leftBotX, leftBotY);
    sprite.draw();
    Uint32 spriteN = (ticks / 100) % PORTALN;
    sprite.setSourceXY(spriteN * PORTALW, PORTALW + 1);
    sprite.setLeftBotXY(leftBotX, leftBotY + PORTALANIMDESPL);
    sprite.draw();
}