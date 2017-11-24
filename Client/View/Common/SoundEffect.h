#ifndef TOWERDEFENSE_SOUNDEFFECT_H
#define TOWERDEFENSE_SOUNDEFFECT_H

#include <SDL_timer.h>
#include <SDL_mixer.h>

class SoundEffect {
private:
    Mix_Chunk *chunk;
    Uint32 time;
    bool canBeDropped;
public:
    SoundEffect(Mix_Chunk *chunk, bool canBeDropped);
    void play();
    bool shouldBeDropped();
};


#endif //TOWERDEFENSE_SOUNDEFFECT_H
