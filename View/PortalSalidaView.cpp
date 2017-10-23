#include "PortalSalidaView.h"
#include "SpriteNamesConfig.h"

#define PORTALSALIDALEFTBOTX 20
#define PORTALSALIDALEFTBOTY 75

PortalSalidaView::PortalSalidaView(TextureLoader &textures,
                                     Renderer &renderer) :
        PortalView(PORTALSALIDA, textures, renderer) {
    leftBotX = PORTALSALIDALEFTBOTX;
    leftBotY = PORTALSALIDALEFTBOTY;
}

PortalSalidaView::~PortalSalidaView() {}