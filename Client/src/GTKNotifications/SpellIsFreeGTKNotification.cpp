//
// Created by tino on 27/11/17.
//

#include "../../include/GTKNotifications/SpellIsFreeGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


SpellIsFreeGTKNotification::SpellIsFreeGTKNotification(SPELL_TYPE type) : _spelltype(type) {

}

SpellIsFreeGTKNotification::~SpellIsFreeGTKNotification() {

}

void SpellIsFreeGTKNotification::Execute(GTKmmRunner &runner) {

    switch(_spelltype){
        case SPELL_TYPE_WATER:
            runner.fixed_lobby.toggle_water->set_sensitive(true);
            runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
            break;
        case SPELL_TYPE_GROUND:
            runner.fixed_lobby.toggle_ground->set_sensitive(true);
            runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
            break;
        case SPELL_TYPE_FIRE:
            runner.fixed_lobby.toggle_fire->set_sensitive(true);
            runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
            break;
        case SPELL_TYPE_AIR:
            runner.fixed_lobby.toggle_air->set_sensitive(true);
            runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
            break;
    }

}