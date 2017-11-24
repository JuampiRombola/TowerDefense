#include "MusicPlayer.h"
#include "SpriteNamesConfig.h"

MusicPlayer::MusicPlayer(MusicLoader &musicLoader) : musicLoader(musicLoader) { }

void MusicPlayer::addShoot(int key) {
    switch (key) {
        case DISPARO_FUEGO:
            effects.emplace_back(musicLoader.getChunk(DISPARO_TIERRA_SONIDO), true);
            break;
        default:
            break;
    }
}

void MusicPlayer::playMusic() {
    for (int channel = 1; channel <= 10 && !effects.empty(); ++channel) {
        if (!Mix_Playing(channel)) {
            auto effect = effects.front();
            if (!effect.shouldBeDropped())
                effect.play();
            effects.pop_front();
        }
    }
}