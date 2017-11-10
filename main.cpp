
#include "GTKRunner.h"
#include "SDLRunner.h"


int main(int argc, char** argv) {

    bool go = false;

    GTKRunner gtk;

    gtk.Run(&argc, &argv);

    if (!go) return 0;

    SDLRunner sdl;

}
