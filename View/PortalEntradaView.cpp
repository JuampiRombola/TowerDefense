#include "PortalEntradaView.h"
#include "SpriteNamesConfig.h"

#define PORTALENTRADALEFTBOTX 18
#define PORTALENTRADALEFTBOTY 100

PortalEntradaView::PortalEntradaView(TextureLoader &textures,
                                     Renderer &renderer) :
        PortalView(PORTALENTRADA, textures, renderer) {
    leftBotX = PORTALENTRADALEFTBOTX;
    leftBotY = PORTALENTRADALEFTBOTY;
}

PortalEntradaView::~PortalEntradaView() {}
