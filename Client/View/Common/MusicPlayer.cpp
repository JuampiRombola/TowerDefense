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

void MusicPlayer::addSpell(int key) {
    switch (key) {
        case RAYO:
            effects.emplace_back(musicLoader.getChunk(RAYO_SONIDO), true);
            break;
        case METEORITO:
            effects.emplace_back(musicLoader.getChunk(METEORITO_SONIDO), true);
            break;
        case TORNADO:
            effects.emplace_back(musicLoader.getChunk(TORNADO_SONIDO), true);
            break;
        case FIREWALL:
            effects.emplace_back(musicLoader.getChunk(FIREWALL_SONIDO), true);
            break;
        case VENTISCA:
            effects.emplace_back(musicLoader.getChunk(VENTISCA_SONIDO), true);
            break;
        case GRIETA:
            effects.emplace_back(musicLoader.getChunk(GRIETA_SONIDO), true);
            break;
        case CONGELACION:
            effects.emplace_back(musicLoader.getChunk(CONGELACION_SONIDO), true);
            break;
        case PING:
            effects.emplace_back(musicLoader.getChunk(PING_SONIDO), true);
        default:
            break;
    }
}

void MusicPlayer::playMusic() {
    for (int channel = 1; channel <= 3 && !effects.empty(); ++channel) {
        if (!Mix_Playing(channel)) {
            auto effect = effects.front();
            if (!effect.shouldBeDropped())
                effect.play();
            effects.pop_front();
        }
    }
}