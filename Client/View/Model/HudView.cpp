#include "HudView.h"
#include "../../include/NetCommands/ClientCastSpellCommand.h"


HudView::HudView(Window &w, TextureLoader &tl, Renderer &r,
                 CommandDispatcher &cd, ModelView &model) :
        textureLoader(tl), renderer(r), dispatcher(cd),
        mouse_y(-1), mousePosition(mouse_x, mouse_y),
        currentCommand(-1),
        buttons(w, mousePosition, r, tl, currentCommand),
        model(model), upgradeTarget(nullptr) {
    arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    crosshair = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
}


HudView::~HudView() {
    if (arrow) SDL_FreeCursor(arrow);
    if (crosshair) SDL_FreeCursor(crosshair);
}

void HudView::getMouseState() {
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mousePosition.activate();
    mousePosition.desactivateMark();
}

void HudView::getFingerState(SDL_Event &event) {
    mouse_x = static_cast<int>(event.tfinger.x);
    mouse_y = static_cast<int>(event.tfinger.y);
    mousePosition.activate();
    mousePosition.desactivateMark();
}

void HudView::doMouseAction() {
    if (!mousePosition.isActive()) return;
    if (upgradeTarget && upgradeTarget->isClicked()) {
        upgradeTarget->onClick();
        SDL_SetCursor(arrow);
        if (currentCommand >= CMD_DAMAGE) {
            //send Command Upgrade.type()
            currentCommand = -1;
            SDL_SetCursor(arrow);
        }
        mousePosition.deactivate();
        return;
    }

    if (buttons.isAnyClicked()) {
        SDL_SetCursor(crosshair);
        return;
    }

    if (!buttons.isAnyClicked() && currentCommand != -1) {
        int tileX = renderer.pixelToCartesianX(mouse_x, mouse_y);
        int tileY = renderer.pixelToCartesianY(mouse_x, mouse_y);
        if (model.isValidTile(tileX, tileY))
            this->sendCommand(tileX, tileY);
        mousePosition.deactivate();
        currentCommand = -1;
        SDL_SetCursor(arrow);
        return;
    }

    mousePosition.deactivate();
    if (buttons.isAnyFakeClicked())
        return;
    int isoX = renderer.pixelToCartesianX(mouse_x, mouse_y);
    int isoY = renderer.pixelToCartesianY(mouse_x, mouse_y);
    if (!model.isValidTile(isoX, isoY)) {
        if (upgradeTarget) {
            delete upgradeTarget;
            upgradeTarget = nullptr;
        }
        return;
    }
    TowerView *target = model.onClick(isoX, isoY);
    if (!target) {
        if (upgradeTarget) {
            delete upgradeTarget;
            upgradeTarget = nullptr;
        }
        return;
    }
    this->updateTarget(target);
}

void HudView::sendCommand(int x, int y) {
//    printf("OPCODE %d en la posicion (%d, %d)\n",currentCommand, x, y);
    NetCommand *command;
    if (currentCommand < 4){
        switch(currentCommand){
            case CMD_EARTH_TOWER:
                command = new ClientBuildTowerCommand(SPELL_TYPE_GROUND, x, y);
                break;
            case CMD_FIRE_TOWER:
                command = new ClientBuildTowerCommand(SPELL_TYPE_FIRE, x, y);
                break;
            case CMD_AIR_TOWER:
                command = new ClientBuildTowerCommand(SPELL_TYPE_AIR, x, y);
                break;
            case CMD_WATER_TOWER:
                command = new ClientBuildTowerCommand(SPELL_TYPE_WATER, x, y);
                break;
        }
    } else {
        switch(currentCommand){
            case CMD_TERRAFORMING:
                command = new ClientCastSpellCommand(SPELL_TERRAFORMING, x, y);
                break;
            case CMD_GRIETA:
                command = new ClientCastSpellCommand(SPELL_GRIETA, x, y);
                break;
            case CMD_METEORITO:
                command = new ClientCastSpellCommand(SPELL_METEORITO, x, y);
                break;
            case CMD_FIREWALL:
                command = new ClientCastSpellCommand(SPELL_FIREWALL, x, y);
                break;
            case CMD_VENTISCA:
                std::cout << "\n\n CMD_VENTISCA " << std::flush;
                command = new ClientCastSpellCommand(SPELL_VENTISCA, x, y);
                break;
            case CMD_CONGELACION:
                std::cout << "\n\n CMD_CONGELACION " << std::flush;
                command = new ClientCastSpellCommand(SPELL_CONGELACION, x, y);
                break;
            case CMD_TORNADO:
                std::cout << "\n\n CMD_TORNADO " << std::flush;
                command = new ClientCastSpellCommand(SPELL_TORNADO, x, y);
                break;
            case CMD_RAYO:
                std::cout << "\n\n CMD_RAYO " << std::flush;
                command = new ClientCastSpellCommand(SPELL_RAYO, x, y);
                break;
        }
    }
    
    dispatcher.QueueCommand(command);
}

void HudView::draw() {
    buttons.draw();
    if (upgradeTarget)
        upgradeTarget->draw();
}

void HudView::addElementalButtons(int key) {
    buttons.addTowerButtons(key);
}

void HudView::getMouseButtonDown() {
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mousePosition.activateMark();
}

void HudView::getFingerButtonDown(SDL_Event &event) {
    mouse_x = static_cast<int>(event.tfinger.x);
    mouse_y = static_cast<int>(event.tfinger.y);
    mousePosition.activateMark();
}

void HudView::updateTarget(TowerView *target) {
    if (upgradeTarget) delete upgradeTarget;
    upgradeTarget = new UpgradeView(renderer, textureLoader,
                                    target, currentCommand, mousePosition);
}
