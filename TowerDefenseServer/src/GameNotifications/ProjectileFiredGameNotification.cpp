
#include "../../include/GameNotifications/ProjectileFiredGameNotification.h"
#include "../../../View/Common/SpriteNamesConfig.h"
#include <iostream>
ProjectileFiredGameNotification::ProjectileFiredGameNotification(ProjectileVM&
viewmodel) : vm(viewmodel){

}

ProjectileFiredGameNotification::~ProjectileFiredGameNotification(){

}

void ProjectileFiredGameNotification::NotifyUnits(std::vector<UnitView*>&
units, TextureLoader &textures, Renderer &renderer){

// a mi que

}

void ProjectileFiredGameNotification::NotifyShots(
        std::vector<ShotView *> &shots, TextureLoader &textures,
        Renderer &renderer) {



    ShotView* shot = new ShotView(DISPARO_TIERRA, textures, renderer);

    shot->shoot(vm.fromXpos, vm.fromYpos, vm.toXpos, vm.toYpos, 200);

    shots.push_back(shot);
}