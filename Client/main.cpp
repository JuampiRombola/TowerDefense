
#include "GTKRunner.h"
#include "SDLRunner.h"

int main(int argc, char** argv) {
    ClientLobbyManager* lobbyManager;
    CommandDispatcher* dispatcher;
    NotificationReciever* reciever;
    ClientSocket* sock;
    bool runsdl = false;
    
    {
        GTKRunner gtk;
        gtk.Run(&argc, &argv);
        lobbyManager = gtk.lobbyManager;
        dispatcher = gtk.dispatcher;
        reciever = gtk.reciever;
        sock = gtk.sock;
        runsdl = gtk.OK;
    }

    if (!runsdl) return 0;

    SDLRunner sdl;

    sdl.Run(dispatcher, reciever, lobbyManager, sock);

    return 0;
}