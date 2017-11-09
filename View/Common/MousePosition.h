#ifndef TOWERDEFENSE_MOUSEPOSITION_H
#define TOWERDEFENSE_MOUSEPOSITION_H

class MousePosition {
private:
    int &x;
    int &y;
    bool active;
public:
    MousePosition(int &x, int&y);
    ~MousePosition();
    int getPosX();
    int getPosY();
    bool isActive();
    void activate();
    void deactivate();
};

#endif //TOWERDEFENSE_MOUSEPOSITION_H
