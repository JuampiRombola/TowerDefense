//
// Created by tino on 20/11/17.
//

#include "../../../include/GameModel/GameNotifications/MapTransferNotification.h"


MapTransferNotification::MapTransferNotification(Map &map, PlayerProxy &player)
: _map(map), _player(player)
{

}
MapTransferNotification::~MapTransferNotification() {

}

void MapTransferNotification::Notify(std::vector<PlayerProxy*> playersToNotify) {
    _map.TransferMapTo(_player);
}