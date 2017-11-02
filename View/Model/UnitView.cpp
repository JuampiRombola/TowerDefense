#include "UnitView.h"

#define WALKING_W_POS 1765
#define WALKING_H_POS 3537

#define WALKING_W 106
#define WALKING_H 119

#define WALKING_OFFSET_X 10
#define WALKING_OFFSET_Y 78

#define DYING_W 0
#define DYING_H 0

#define UNIT_WALKING_N 12
#define UNIT_DYING_N 18

#define PIXELS 40

UnitView::UnitView(int key, TextureLoader &textures, Renderer &renderer) :
        spriteWalking(textures.getTexture(key), renderer),
        spriteDying(textures.getTexture(key), renderer) {
    currentDirection = SE;
    this->setCurrentDirection();
    currentState = WALKING;
    spriteWalking.setSourceRect(WALKING_W_POS, WALKING_H_POS, WALKING_W, WALKING_H);
    spriteWalking.setDestRect(x, y, WALKING_W, WALKING_H);
    spriteWalking.setOffsetXY(WALKING_OFFSET_X, WALKING_OFFSET_Y);
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
    Uint32 spriteN;
    if (currentState == WALKING) {
        if (accumulatedDisplacement < PIXELS) {
            this->setNumberOfPixelsToMove(ticks);
            this->setOffsetXY();
        }
        spriteN = (ticks / timePerPixel) % UNIT_WALKING_N;
        spriteWalking.setSourceXY(spriteN * WALKING_W + WALKING_W_POS,
                                  WALKING_H_POS + currentDirection * WALKING_H);
        spriteWalking.draw();
    } else {
        spriteN = (ticks / timePerPixel) % UNIT_DYING_N;
        spriteWalking.setSourceXY(spriteN * DYING_W + WALKING_W_POS,
                                  WALKING_H_POS + currentDirection * DYING_H);
        spriteWalking.draw();
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
