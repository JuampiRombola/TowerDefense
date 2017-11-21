#include "HudView.h"
#include "../../include/NetCommands/ClientCastSpellCommand.h"


HudView::HudView(Window &w, TextureLoader &tl, Renderer &r,
                 CommandDispatcher &cd) :
        textureLoader(tl), renderer(r), dispatcher(cd),
        mouse_y(-1), mousePosition(mouse_x, mouse_y),
        currentCommand(-1),
        buttons(w, mousePosition, r, tl, cd, currentCommand) {
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
}

void HudView::getFingerState(SDL_Event &event) {
    mouse_x = static_cast<int>(event.tfinger.x);
    mouse_y = static_cast<int>(event.tfinger.y);
    mousePosition.activate();
}

void HudView::doMouseAction() {
    if (!mousePosition.isActive()) return;

    if (buttons.isAnyClicked())
        SDL_SetCursor(crosshair);

    if (!buttons.isAnyClicked() && currentCommand != -1) {
        int tileX = renderer.pixelToCartesianX(mouse_x, mouse_y);
        int tileY = renderer.pixelToCartesianY(mouse_x, mouse_y);
        this->sendCommand(tileX, tileY);
        mousePosition.deactivate();
        currentCommand = -1;
        SDL_SetCursor(arrow);
    }
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
}

void HudView::addElementalButtons(int key) {
    buttons.addTowerButtons(key);
}
