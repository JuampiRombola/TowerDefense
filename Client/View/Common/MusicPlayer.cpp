#include "MusicPlayer.h"
#include "SpriteNamesConfig.h"

MusicPlayer::MusicPlayer(MusicLoader &musicLoader) : musicLoader(musicLoader) { }

void MusicPlayer::addShoot(int key) {
    int shootSound;
    switch (key) {
        case DISPARO_FUEGO:
            shootSound = DISPARO_FUEGO_SONIDO;
            break;
        case DISPARO_TIERRA:
            shootSound = DISPARO_TIERRA_SONIDO;
            break;
        case DISPARO_AIRE:
            shootSound = DISPARO_AIRE_SONIDO;
            break;
        case DISPARO_AGUA:
            shootSound = DISPARO_AGUA_SONIDO;
            break;
        default:
            return;
    }
    effects.emplace_back(musicLoader.getChunk(shootSound), true);
}

void MusicPlayer::addDyingEnemy() {
    effects.emplace_back(musicLoader.getChunk(ENEMIGO_MUERTE_SONIDO), true);
}

void MusicPlayer::addSpell(int key) {
    int spellSound;
    switch (key) {
        case RAYO:
            spellSound = RAYO_SONIDO;
            break;
        case METEORITO:
            spellSound = METEORITO_SONIDO;
            break;
        case TORNADO:
            spellSound = TORNADO_SONIDO;
            break;
        case FIREWALL:
            spellSound = FIREWALL_SONIDO;
            break;
        case VENTISCA:
            spellSound = VENTISCA_SONIDO;
            break;
        case GRIETA:
            spellSound = GRIETA_SONIDO;
            break;
        case CONGELACION:
            spellSound = CONGELACION_SONIDO;
            break;
        case PING:
            spellSound = PING_SONIDO;
            break;
        default:
            return;
    }
    effects.emplace_back(musicLoader.getChunk(spellSound), true);
}

void MusicPlayer::gameOver() {
    effects.emplace_back(musicLoader.getChunk(DEFEAT_SONIDO), false);
}

void MusicPlayer::win() {
    effects.emplace_back(musicLoader.getChunk(WIN_SONIDO), false);
}

void MusicPlayer::addStructureTile() {
    effects.emplace_back(musicLoader.getChunk(TERRAFORMING_SONIDO), true);
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