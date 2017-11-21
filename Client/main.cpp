
#include "GTKRunner.h"
#include "SDLRunner.h"

int main(int argc, char** argv) {
    ClientLobbyManager* lobbyManager;
    CommandDispatcher* dispatcher;
    NotificationReciever* reciever;
    ClientSocket* sock;
    
    GTKRunner gtk;
    gtk.Run(&argc, &argv);
    lobbyManager = gtk.lobbyManager;
    dispatcher = gtk.dispatcher;
    reciever = gtk.reciever;
    sock = gtk.sock;

    if (gtk.OK){
        SDLRunner sdl(gtk.MapSurface, gtk.MapWidth, gtk.MapHeight);
        sdl.Run(dispatcher, reciever, lobbyManager, sock);      
    }
    
    return 0;
}