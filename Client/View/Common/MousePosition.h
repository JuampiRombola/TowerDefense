#ifndef TOWERDEFENSE_MOUSEPOSITION_H
#define TOWERDEFENSE_MOUSEPOSITION_H

class MousePosition {
private:
    int &x;
    int &y;
    bool active;
    bool marked;
public:
    MousePosition(int &x, int&y);
    ~MousePosition();
    int getPosX();
    int getPosY();
    bool isActive();
    void activate();
    void deactivate();
    bool isMarked();
    void activateMark();
    void desactivateMark();
};

#endif //TOWERDEFENSE_MOUSEPOSITION_H
