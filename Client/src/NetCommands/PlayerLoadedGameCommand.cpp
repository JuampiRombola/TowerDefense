//
// Created by tino on 19/11/17.
//

#include "../../include/NetCommands/PlayerLoadedGameCommand.h"
#include "../../../Common/Protocolo.h"

PlayerLoadedGameCommand::PlayerLoadedGameCommand()
{

}

PlayerLoadedGameCommand::~PlayerLoadedGameCommand(){

}

void PlayerLoadedGameCommand::SendCommand(SocketWrapper& sock){
    uint8_t instruction = CLIENT_LOADED_GAME;
    sock.Send((char*)&instruction, 1);
}