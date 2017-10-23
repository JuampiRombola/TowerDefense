#ifndef TOWERDEFENSE_PORTALVIEW_H
#define TOWERDEFENSE_PORTALVIEW_H

#include "View.h"

class PortalView : public View {
public:
    PortalView(int key, TextureLoader &textures, Renderer &renderer);
    ~PortalView();
    void draw(Uint32 ticks) override;
};


#endif //TOWERDEFENSE_PORTALVIEW_H
