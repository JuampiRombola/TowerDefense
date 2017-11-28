
#include "GTKmm/GTKmmRunner.h"
#include "SDLRunner.h"

int main(int argc, char** argv) {
    ClientLobbyManager* lobbyManager;
    CommandDispatcher* dispatcher;
    NotificationReciever* reciever;
    ClientSocket* sock;

    bool finish = false;

    while (!finish){
        GTKmmRunner gtk;
        gtk.Run(&argc, &argv);
        lobbyManager = gtk.lobbyManager;
        dispatcher = gtk.dispatcher;
        reciever = gtk.reciever;
        sock = gtk.sock;

        if (gtk.OK){
            SDLRunner sdl(gtk.MapSurface, gtk.MapWidth, gtk.MapHeight);
            sdl.Run(dispatcher, reciever, lobbyManager, sock);
        } else
            finish = true;
    }

    return 0;
}