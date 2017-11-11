#include "AnimatedSprite.h"

#define DEFAULT_TIME 100

AnimatedSprite::AnimatedSprite(SDL_Texture *texture, Renderer &renderer,
                               int width, int height,
                               int startX, int startY,
                               int totalColumns, int totalRows) :
        Sprite(texture, renderer),
        width(width), height(height),
        startX(startX), startY(startY),
        totalColumns(totalColumns), totalRows(totalRows), i(0), j(0) {
    this->setSourceRect(startX, startY, width, height);
    this->setDestRect(0, 0, width, height);
    timePerSprite = DEFAULT_TIME;
    display = LOOP;
}

void AnimatedSprite::next(Uint32 ticks) {
    int nextSprite = (ticks / timePerSprite) % (totalColumns * totalRows);
    if (currentSprite == nextSprite) return;
    currentSprite = nextSprite;

    if ((i + 1) == totalColumns && totalRows >= 2)
        ++j = j % totalRows;

    if (totalColumns >= 2)
        ++i = i % totalColumns;
    this->setSourceXY(i * width + startX, j * height + startY);
}

void AnimatedSprite::nextAndDraw(Uint32 ticks) {
    if ((i+1) == totalColumns && (j+1) == totalRows) {
        if (display == ONCE) return;
        if (display == FROZEN) {
            this->draw();
            return;
        }
    }
    this->next(ticks);
    this->draw();
}

void AnimatedSprite::setTimePerSprite(Uint32 t) {
    timePerSprite = t;
}

void AnimatedSprite::setStartXStartY(int sx, int sy) {
    startX = sx;
    startY = sy;
}

int AnimatedSprite::getCurrentSprite() {
    return ((i + 1) * (j + 1));
}

void AnimatedSprite::reset() {
    i = 0;
    j = 0;
}

void AnimatedSprite::setDisplayMode(int mode) {
    display = mode;
}
