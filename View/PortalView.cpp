#include "PortalView.h"

#define PORTALW 138
#define PORTALH 181

#define PORTALN 30

PortalView::PortalView(int key, TextureLoader &textures, Renderer &renderer) :
        View(key, textures, renderer) {
    sprite.setSourceRect(0, 0, PORTALW, PORTALH);
    sprite.setDestRect(x, y, PORTALW, PORTALH);
}

PortalView::~PortalView() {}

void PortalView::draw(Uint32 ticks) {
    Uint32 spriteN = (ticks / 100) % PORTALN;
    sprite.setSourceXY(spriteN * PORTALW, PORTALW + 1);

    sprite.draw();
    sprite.setSourceXY(0, 0);
    sprite.draw();
}