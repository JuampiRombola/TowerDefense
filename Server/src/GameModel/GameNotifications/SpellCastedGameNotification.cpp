
#include <iostream>
#include "../../../include/GameModel/GameNotifications/SpellCastedGameNotification.h"

SpellCastedGameNotification::SpellCastedGameNotification(CAST_SPELL_TYPE type, uint32_t x, uint32_t y, uint32_t duration_ms, std::vector<PlayerProxy*> playersToNotify)
        : GameNotification(playersToNotify), _type(type), _x(x), _y(y), _duration_ms(duration_ms)
{

}

SpellCastedGameNotification::~SpellCastedGameNotification(){

}

void SpellCastedGameNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = CLIENT_CAST_SPELL;
        if (_type == SPELL_RAYO)
            std::cout << "\n\n SENDING RAyos \n\n" << std::flush;
        p->SendByte(opcode);
        p->SendByte(_type);
        p->SendInt32(_x);
        p->SendInt32(_y);
        p->SendInt32(_duration_ms);
    }
}