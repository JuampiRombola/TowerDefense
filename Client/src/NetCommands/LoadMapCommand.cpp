//
// Created by tino on 20/11/17.
//

#include "../../include/NetCommands/LoadMapCommand.h"
#include "../../../Common/Protocolo.h"


LoadMapCommand::LoadMapCommand() {

}

LoadMapCommand::~LoadMapCommand(){

}


void LoadMapCommand::SendCommand(SocketWrapper& sock){
    uint8_t opcode = LOAD_MAP;
    sock.SendByte(opcode);
}