#include "MusicPlayer.h"
#include "SpriteNamesConfig.h"

MusicPlayer::MusicPlayer(MusicLoader &musicLoader) : musicLoader(musicLoader) { }

void MusicPlayer::addShoot(int key) {
    switch (key) {
        case DISPARO_FUEGO:
            effects.emplace_back(musicLoader.getChunk(DISPARO_FUEGO_SONIDO), true);
            break;
        case DISPARO_TIERRA:
            effects.emplace_back(musicLoader.getChunk(DISPARO_TIERRA_SONIDO), true);
            break;
        case DISPARO_AIRE:
            effects.emplace_back(musicLoader.getChunk(DISPARO_AIRE_SONIDO), true);
            break;
        case DISPARO_AGUA:
            effects.emplace_back(musicLoader.getChunk(DISPARO_AGUA_SONIDO), true);
            break;
        default:
            break;
    }
}

void MusicPlayer::addDyingEnemy() {
    effects.emplace_back(musicLoader.getChunk(ENEMIGO_MUERTE_SONIDO), true);
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