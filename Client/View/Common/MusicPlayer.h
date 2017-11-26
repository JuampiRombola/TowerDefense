#ifndef TOWERDEFENSE_MUSICPLAYER_H
#define TOWERDEFENSE_MUSICPLAYER_H

#include <list>
#include "MusicLoader.h"
#include "SoundEffect.h"

class MusicPlayer {
private:
    MusicLoader &musicLoader;
    std::list<SoundEffect> effects;
public:
    MusicPlayer(MusicLoader &musicLoader);
    void addShoot(int key);
    void addDyingEnemy();
    void addSpell(int key);
    void gameOver();
    void win();
    void addStructureTile();
    void playMusic();
};


#endif //TOWERDEFENSE_MUSICPLAYER_H
