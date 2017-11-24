#ifndef TOWERDEFENSE_MUSICLOADER_H
#define TOWERDEFENSE_MUSICLOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include "MusicNamesConfig.h"

class MusicLoader {
private:
    std::map<int, Mix_Chunk *> effects;
    Mix_Music *music;
public:
    MusicLoader();

    void playMusic();

    Mix_Chunk *getChunk(int chunkName);

    ~MusicLoader();
};


#endif //TOWERDEFENSE_MUSICLOADER_H
