#ifndef TOWERDEFENSE_PORTALENTRADAVIEW_H
#define TOWERDEFENSE_PORTALENTRADAVIEW_H


#include "PortalView.h"

class PortalEntradaView : public PortalView {
public:
    PortalEntradaView(TextureLoader &textures, Renderer &renderer);
    ~PortalEntradaView();
    std::string getType();
};


#endif //TOWERDEFENSE_PORTALENTRADAVIEW_H
