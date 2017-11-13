
#include "GTKRunner.h"
#include "SDLRunner.h"

int main(int argc, char** argv) {
    GTKRunner gtk;
    gtk.Run(&argc, &argv);
    if (!gtk.OK)
        return 0;
    SDLRunner sdl;
    sdl.Run();
    return 0;
}

/*
if (argc < 3)
return 0;

std::string serverIp = *(argv + 1);
std::string port = *(argv + 2);
std::string pname = *(argv + 3);
std::string create = *(argv + 4);

ClientSocket sock(serverIp, port);

if (!sock.Connected()){
std::cout << "FAILED TO CONNECT\n";
return -1;
}

std::cout << "CONNECTED\n";

GUINotificationQueue guiNotiQueue;
ClientLobbyManager lobbyManager(guiNotiQueue, sock);
NotificationReciever reciever(sock, lobbyManager, guiNotiQueue);
CommandDispatcher dispatcher(sock);


reciever.Run();
dispatcher.Run();

LogInCommand login(pname);
dispatcher.QueueCommand(&login);


std::this_thread::sleep_for (std::chrono::milliseconds(2500));

GetLobbiesCommand getlobbies;
dispatcher.QueueCommand(&getlobbies);

std::this_thread::sleep_for (std::chrono::milliseconds(2500));


if (create == "create1"){
std::string lobbyName = "Un lobby1";
CreateLobbyCommand newlobby(lobbyName);
dispatcher.QueueCommand(&newlobby);
}
if (create == "create2"){
std::string lobbyName = "Un lobby2";
CreateLobbyCommand newlobby(lobbyName);
dispatcher.QueueCommand(&newlobby);
}

std::this_thread::sleep_for (std::chrono::milliseconds(2500));

JoinLobbyCommand join(1);
dispatcher.QueueCommand(&join);
LeaveLobbyCommand leave;

//   std::string lobbyName2 = "Otro lobby";
//   CreateLobbyCommand newlobby2(lobbyName2);
//   dispatcher.QueueCommand(&newlobby2);
int i = 0;
while (true){
i++;
//  if (i == 4){
//    dispatcher.QueueCommand(&leave);
//} else if ( i == 10 ){
//   dispatcher.QueueCommand(&join);
//}
std::this_thread::sleep_for (std::chrono::milliseconds(2500));
std::cout << "POLLING GUI: i: " << i << "\n" << std::flush;
SDLNotification* noti = guiNotiQueue.GetGUINotification();
while (noti != nullptr){
//refresco la gui con la notificacion
noti->Execute();
delete noti;
noti = guiNotiQueue.GetGUINotification();
}
}


getchar();
dispatcher.Stop();

return 0;
*/
