#ifndef TOWERDEFENSE_WAITACTIONBUTTON_H
#define TOWERDEFENSE_WAITACTIONBUTTON_H


#include "GameButton.h"
#include "../Common/Announcement.h"

class WaitActionButton : public GameButton {
private:
    Uint32 t;
    Announcement *keySym;
public:
    WaitActionButton(Renderer &r, TextureLoader &tl,
        int spriteKey, MousePosition &mousePosition,
        int x, int y, int w, int h, int &cmd, std::string &s);
    ~WaitActionButton();
    void draw() override;
private:
    void mapKey(int spriteKey);
};


#endif //TOWERDEFENSE_WAITACTIONBUTTON_H
