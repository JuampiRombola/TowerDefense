#ifndef TOWERDEFENSE_PORTALSALIDAVIEW_H
#define TOWERDEFENSE_PORTALSALIDAVIEW_H

#include "PortalView.h"

class PortalSalidaView : public PortalView {
public:
    PortalSalidaView(TextureLoader &textures, Renderer &renderer);
    ~PortalSalidaView() override;
    std::string getType();
};



#endif //TOWERDEFENSE_PORTALSALIDAVIEW_H
