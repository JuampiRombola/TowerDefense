
#include "GTKRunner.h"
#include "SDLRunner.h"


int main(int argc, char** argv) {

    bool go = true;

    GTKRunner gtk;

    gtk.Run(&argc, &argv);

    if (!go) return 0;

    SDLRunner sdl;

    sdl.Run();

    return 0;

}
