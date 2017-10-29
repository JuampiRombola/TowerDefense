#ifndef TOWERDEFENSE_VIEW_H
#define TOWERDEFENSE_VIEW_H

#include <SDL_types.h>

class View {
protected:
    int x;
    int y;

public:
    View();
    virtual ~View();
    virtual void draw(Uint32 ticks) = 0;
    virtual void setXY(int x, int y);
    int getX();
    int getY();
};


#endif //TOWERDEFENSE_VIEW_H
