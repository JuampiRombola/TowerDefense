
#include "../../include/GameNotifications/UnitPositionGameNotification.h"
#include "../../../View/Common/SpriteNamesConfig.h"
#include "../../../View/Model/ShotView.h"
#include <iostream>
UnitPositionGameNotification::UnitPositionGameNotification(UnitVM& viewmodel) : vm(viewmodel){

}

UnitPositionGameNotification::~UnitPositionGameNotification(){

}

void UnitPositionGameNotification::NotifyShots(
        std::vector<ShotView *> &shots, TextureLoader &textures,
        Renderer &renderer) {
//a mi que
}

void UnitPositionGameNotification::NotifyUnits(std::vector<UnitView*>& units,
                                           TextureLoader &textures, Renderer &renderer){
    std::cout << "NOTI TILE\n" << std::flush;
    bool found = false;
    for (auto it = units.begin(); it != units.end() && !found; ++it){
        UnitView* uv = *it;
        if (vm.id == uv->getId()){
            found = true;
            uv->move(vm.xPos, vm.yPos, vm.nextXpos, vm.nextYpos, vm.stepDelay_ms);
            std::cout << "from: (" << vm.xPos << ", " << vm.yPos << ") to ("
                      << vm.nextXpos << ", " << vm.nextYpos << "), ms to "
                    "wait: " << vm.stepDelay_ms << "\n";
        }
    }

    if (!found){
        UnitView* view = nullptr;
        switch(vm.unitType){
            case uAbmonible:
                view = new UnitView(vm.id, ABOMINABLE, textures, renderer);
                break;
            case uDemonioVerde:
                view = new UnitView(vm.id, DEMONIOVERDE, textures, renderer);
                break;
            case uEspectro:
                view = new UnitView(vm.id, ESPECTRO, textures, renderer);
                break;
            case uHalconSangriento:
                view = new UnitView(vm.id, HALCONSANGRIENTO, textures, renderer);
                break;
            case uHombreCabra:
                view = new UnitView(vm.id, HOMBRECABRA, textures, renderer);
                break;
            case uNoMuerto:
                view = new UnitView(vm.id, NOMUERTO, textures, renderer);
                break;
        }


        if (view != nullptr){
            view->move(vm.xPos, vm.yPos, vm.nextXpos, vm.nextYpos, vm.stepDelay_ms);
            units.push_back(view);

            std::cout << "FIRST from: (" << vm.xPos << ", " << vm.yPos << ") "
                    "to ("
                      << vm.nextXpos << ", " << vm.nextYpos << "), ms to "
                              "wait: " << vm.stepDelay_ms << "\n";
        }

    }


}