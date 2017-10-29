#include "PortalSalidaView.h"
#include "../Common/SpriteNamesConfig.h"

#define PORTALSALIDAOFFSETX 20
#define PORTALSALIDAOFFSETY 75

PortalSalidaView::PortalSalidaView(TextureLoader &textures,
                                     Renderer &renderer) :
        PortalView(PORTALSALIDA, textures, renderer) {
    spritePortal.setOffsetXY(PORTALSALIDAOFFSETX, PORTALSALIDAOFFSETY);
    spriteAnim.setOffsetXY(PORTALSALIDAOFFSETX,
                           PORTALSALIDAOFFSETY + PORTALANIMOFFSET);
}

PortalSalidaView::~PortalSalidaView() {}