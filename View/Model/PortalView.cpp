#include <iostream>
#include "PortalView.h"

#define PORTALW 138
#define PORTALH 181

#define PORTALN 30

PortalView::PortalView(int key, TextureLoader &textures, Renderer &renderer) :
        spritePortal(textures.getTexture(key), renderer),
        spriteAnim(textures.getTexture(key), renderer) {

    spritePortal.setSourceRect(0, 0, PORTALW, PORTALH);
    spritePortal.setDestRect(x, y, PORTALW, PORTALH);

    spriteAnim.setSourceRect(0, 0, PORTALW, PORTALH + 1);
    spriteAnim.setDestRect(x, y, PORTALW, PORTALH);
}

PortalView::~PortalView() {}

void PortalView::draw(Uint32 ticks) {
    spritePortal.draw();

    Uint32 spriteN = (ticks / 100) % PORTALN;
    spriteAnim.setSourceXY(spriteN * PORTALW, PORTALW + 1);
    spriteAnim.draw();
}

void PortalView::setXY(int x, int y) {
    View::setXY(x, y);
    spritePortal.setDestXY(x, y);
    spriteAnim.setDestXY(x, y);
}
