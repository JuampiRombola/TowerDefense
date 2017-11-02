#include "UnitView.h"

#define WALKING_W 106
#define WALKING_H 119
#define WALKING_START_X 1765
#define WALKING_START_Y 3537
#define WALKING_COLUMNS 12
#define WALKING_ROWS 1
#define WALKING_OFFSET_X 10
#define WALKING_OFFSET_Y 78

#define DYING_W 201
#define DYING_H 155
#define DYING_START_X 1
#define DYING_START_Y 2273
#define DYING_COLUMNS 18
#define DYING_ROWS 1
#define DYING_OFFSET_X 48
#define DYING_OFFSET_Y 0

#define PIXELS 40

UnitView::UnitView(int key, TextureLoader &textures, Renderer &renderer) :
        spriteWalking(textures.getTexture(key), renderer,
                      WALKING_W, WALKING_H,
                      WALKING_START_X, WALKING_START_Y,
                      WALKING_COLUMNS, WALKING_ROWS),
        spriteDying(textures.getTexture(key), renderer,
                    DYING_W, DYING_H,
                    DYING_START_X, DYING_START_Y,
                    DYING_COLUMNS, DYING_ROWS) {
    currentDirection = SE;
    this->setCurrentDirection();
    currentState = WALKING;

    spriteWalking.setDestRect(x, y, WALKING_W, WALKING_H);
    spriteWalking.setOffsetXY(WALKING_OFFSET_X, WALKING_OFFSET_Y);

    spriteDying.setDestRect(x, y, DYING_W, DYING_H);
}

void UnitView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteWalking.setDestXY(x, y);
    int offsetX = WALKING_OFFSET_X;
    int offsetY = WALKING_OFFSET_Y;
    if (currentDirection == SO || currentDirection == NO)
        offsetX -= PIXELS * 2;
    if (currentDirection == NE || currentDirection == NO)
        offsetY -= PIXELS;
    spriteWalking.setOffsetXY(offsetX, offsetY);
}

void UnitView::draw(Uint32 ticks) {
    if (currentState == WALKING) {
        if (accumulatedDisplacement < PIXELS) {
            this->setNumberOfPixelsToMove(ticks);
            this->setOffsetXY();
        }
        spriteWalking.setStartXStartY(WALKING_START_X,
                                      WALKING_START_Y
                                      + currentDirection * WALKING_H);
        spriteWalking.setTimePerSprite(timePerPixel);
        spriteWalking.nextAndDraw(ticks);
    } else {
        if (spriteDying.getCurrentSprite() != DYING_COLUMNS)
            spriteDying.nextAndDraw(ticks);
    }
}

void UnitView::move(int x, int y, int nextX, int nextY, Uint32 t) {
    this->setXY(x, y);
    this->nextX = nextX;
    this->nextY = nextY;
    initTime = SDL_GetTicks();
    timePerPixel = t / PIXELS;
    isFirstStep = true;
    accumulatedDisplacement = 0;
}

void UnitView::setNumberOfPixelsToMove(Uint32 currentTime) {
    Uint32 elapsedTime = currentTime - initTime;
    int displacement = elapsedTime / timePerPixel;
    currentDisplacement = displacement - accumulatedDisplacement;

    if (isFirstStep && (displacement >= (PIXELS / 2)))
        currentDisplacement = (PIXELS / 2) - accumulatedDisplacement;

    if (displacement >= PIXELS)
        currentDisplacement = PIXELS - accumulatedDisplacement;

    accumulatedDisplacement += currentDisplacement;
}

void UnitView::setOffsetXY() {
    int x = spriteWalking.getOffsetX() + (directionX * currentDisplacement)*2;
    int y = spriteWalking.getOffsetY() + directionY * currentDisplacement;
    spriteWalking.setOffsetXY(x, y);
    if (isFirstStep && (accumulatedDisplacement == (PIXELS / 2))) {
        isFirstStep = false;
        this->calculateNewDirection();
    }
}

void UnitView::calculateNewDirection() {
    if (nextX == x) {
        if (nextY > y)
            currentDirection = SO;
        else
            currentDirection = NE;
    }

    if (nextY == y) {
        if (nextX > x)
            currentDirection = SE;
        else
            currentDirection = NO;
    }
    this->setCurrentDirection();
}

void UnitView::setCurrentDirection() {
    if (currentDirection == NO) {
        directionX = 1;
        directionY = 1;
    }
    if (currentDirection == SO) {
        directionX = 1;
        directionY = -1;
    }
    if (currentDirection == SE) {
        directionX = -1;
        directionY = -1;
    }
    if (currentDirection == NE) {
        directionX = -1;
        directionY = 1;
    }
}

void UnitView::enableDying() {
    currentState = DYING;
    spriteDying.setDestXY(x, y);
    spriteDying.setTimePerSprite(timePerPixel);
    spriteDying.setStartXStartY(DYING_START_X,
                                DYING_START_Y
                                + currentDirection * DYING_H);
    int offsetX = spriteWalking.getOffsetX() + DYING_OFFSET_X;
    int offsetY = spriteWalking.getOffsetY() + DYING_OFFSET_Y;
    spriteDying.setOffsetXY(offsetX, offsetY);
}
