#ifndef TOWERDEFENSE_TEXTURELOADER_H
#define TOWERDEFENSE_TEXTURELOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class TextureLoader {
private:
    enum PNGS{PRADERA = 0, TIERRAFIRME, CAMINOTIERRA, BOTON_PRUEBA,
        BOTON_PRUEBA_ACTIVO, BOTON_PRUEBA_INACTIVO, LAVA_SELECT,
        DESIERTO_SELECT, GLACIAR_SELECT, PRADERA_SELECT, AGREGAR_HORDA,
        ABMONIBLE_SUMAR, ABMONIBLE_RESTAR, ELIMINAR_HORDA,
        /*PORTALENTRADA,
        PORTALSALIDA, TORRETIERRA, ABOMINABLE,*/ TOTAL};

    std::vector<SDL_Surface *> images;
    std::vector<SDL_Texture *> textures;

public:
    explicit TextureLoader(SDL_Renderer *renderer);
    ~TextureLoader();
    SDL_Texture *getTexture(int pos);
};


#endif //TOWERDEFENSE_TEXTURELOADER_H
