#include <iostream>
#include "SoundEffect.h"

SoundEffect::SoundEffect(Mix_Chunk *chunk, bool canBeDropped) :
        chunk(chunk), time(SDL_GetTicks()), canBeDropped(canBeDropped) {}

void SoundEffect::play() {
    Mix_PlayChannel(-1, chunk, 0);
}

bool SoundEffect::shouldBeDropped() {
    return canBeDropped ? SDL_GetTicks() - time > 100 : false;
}