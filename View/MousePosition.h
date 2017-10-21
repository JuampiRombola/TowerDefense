#ifndef TOWERDEFENSE_MOUSEPOSITION_H
#define TOWERDEFENSE_MOUSEPOSITION_H


class MousePosition {
private:
    int &x;
    int &y;
    bool &active;
public:
    MousePosition(int &x, int&y, bool& active);
    ~MousePosition();
    int getPosX();
    int getPosY();
    bool isActive();
};


#endif //TOWERDEFENSE_MOUSEPOSITION_H
