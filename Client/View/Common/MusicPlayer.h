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
    void playMusic();
};


#endif //TOWERDEFENSE_MUSICPLAYER_H