#ifndef TOWERDEFENSE_SPELLVIEW_H
#define TOWERDEFENSE_SPELLVIEW_H


#include "../Common/AnimatedSprite.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/View.h"

class SpellView : public View {
private:
    const YAML::Node cfg;
    AnimatedSprite sprite;
    Uint32 initTime;
    Uint32 requiredTime;
    bool isEnable;

public:
    SpellView(int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    void cast(int x, int y, Uint32 t);
    bool hasFinished();
};


#endif //TOWERDEFENSE_SPELLVIEW_H
