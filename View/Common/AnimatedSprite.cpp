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
}

void AnimatedSprite::next(Uint32 ticks) {
    int nextSprite = (ticks / timePerSprite) % (totalColumns * totalRows);
    if (currentSprite == nextSprite) return;
    currentSprite = nextSprite;

    if (i == totalColumns && totalRows >= 2)
        ++j = j % totalRows;

    if (totalColumns >= 2)
        ++i = i % totalColumns;

    printf("%d\n", (i * width));
    this->setSourceXY(i * width + startX, j * height + startY);
}

void AnimatedSprite::nextAndDraw(Uint32 ticks) {
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
    return (++i * ++j);
}
