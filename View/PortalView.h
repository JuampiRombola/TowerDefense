#ifndef TOWERDEFENSE_PORTALVIEW_H
#define TOWERDEFENSE_PORTALVIEW_H

#include "View.h"

class PortalView : public View {
protected:
    int leftBotX;
    int leftBotY;

public:
    PortalView(int key, TextureLoader &textures, Renderer &renderer);
    ~PortalView() override;
    void draw(Uint32 ticks) override;
};


#endif //TOWERDEFENSE_PORTALVIEW_H
