#include "PortalEntradaView.h"
#include "SpriteNamesConfig.h"

#define PORTALENTRADAOFFSETX 18
#define PORTALENTRADAOFFSETY 100

PortalEntradaView::PortalEntradaView(TextureLoader &textures,
                                     Renderer &renderer) :
        PortalView(PORTALENTRADA, textures, renderer) {
    spritePortal.setOffsetXY(PORTALENTRADAOFFSETX, PORTALENTRADAOFFSETY);
    spriteAnim.setOffsetXY(PORTALENTRADAOFFSETX,
                           PORTALENTRADAOFFSETY + PORTALANIMOFFSET);
}

PortalEntradaView::~PortalEntradaView() {}
