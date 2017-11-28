#include "ExitView.h"
#include "SpriteNamesConfig.h"

#define EXIT_VIEW_W 426
#define EXIT_VIEW_H 147

#define EXIT_VIEW_BUTTON_W 160
#define EXIT_VIEW_BUTTON_H 45

#define EXIT_OFFSET_OK_X 40
#define EXIT_OFFSET_CANCEL_X 225
#define EXIT_OFFSET_Y 80

ExitView::ExitView(Renderer &renderer, TextureLoader &tl, MousePosition &mp) :
        imageExit(tl.getTexture(EXIT_VIEW), renderer), mousePosition(mp),
        active(false) {
    imageExit.setSourceRect(0, 0, EXIT_VIEW_W, EXIT_VIEW_H);
    imageExit.setDestRect(renderer.getWindowWidth()/2 - EXIT_VIEW_W/2,
                      renderer.getWindowHeight()/2 - EXIT_VIEW_H,
                      EXIT_VIEW_W, EXIT_VIEW_H);
}

bool ExitView::isActive() {
    return active;
}

void ExitView::activate() {
    active = true;
}

void ExitView::desactivate() {
    active = false;
}

bool ExitView::isOk() {
    return this->isClicked(EXIT_OFFSET_OK_X);
}

bool ExitView::isCancel() {
    return this->isClicked(EXIT_OFFSET_CANCEL_X);
}

void ExitView::draw() {
    imageExit.drawEuclidian();
}

bool ExitView::isClicked(int offsetX) {
    int x = mousePosition.getPosX();
    int y = mousePosition.getPosY();
    int buttonX = imageExit.getDestX() + offsetX;
    int buttonY = imageExit.getDestY() + EXIT_OFFSET_Y;
    return (mousePosition.isActive() &&
            !(x < buttonX || x > (buttonX + EXIT_VIEW_BUTTON_W) || 
              y < buttonY || y > (buttonY + EXIT_VIEW_BUTTON_H)));
}
