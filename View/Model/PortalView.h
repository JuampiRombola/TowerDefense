#ifndef TOWERDEFENSE_PORTALVIEW_H
#define TOWERDEFENSE_PORTALVIEW_H

#include "../Common/View.h"
#include "../Common/Sprite.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"

#define PORTALANIMOFFSET 40

class PortalView : public View {
protected:
    Sprite spritePortal;
    Sprite spriteAnim;

public:
    PortalView(int key, TextureLoader &textures, Renderer &renderer);
    ~PortalView() override;
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
};


#endif //TOWERDEFENSE_PORTALVIEW_H
