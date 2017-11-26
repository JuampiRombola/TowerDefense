#ifndef TOWERDEFENSE_MODELVIEW_H
#define TOWERDEFENSE_MODELVIEW_H


#include "ShotView.h"
#include "MapView.h"
#include "DepthLevel.h"
#include "../Common/Announcement.h"
#include "../../include/NonBlockingThreadSafeQueue.h"
#include "../Common/MusicPlayer.h"
#include <mutex>
#include <map>
#include <list>
#include <vector>
#include <condition_variable>

class ModelView {
private:
    Renderer &renderer;
    TextureLoader &textureLoader;
    MapView map;
    std::mutex m;
    std::vector<DepthLevel *> depthLevels;
    std::map<int, int> idDepthLevelsTowers;
    std::map<int, int> idDepthLevelsUnits;
    Announcement* _currentAnnouncement;
    NonBlockingThreadSafeQueue<std::string*> newAnnouncementsMessages;
    MusicPlayer &musicPlayer;
public:
    ModelView(Renderer &renderer, TextureLoader &textureLoader, MusicPlayer &musicPlayer);
    ~ModelView();
    void draw(Uint32 time);
    bool isValidTile(int x, int y);
    void setMapEnvironment(int type);
    void setMapWidthHeight(int w, int h);
    void createPathTile(int x, int y);
    void createStructureTile(int x, int y);
    void createPortalEntrada(int x, int y);
    void createPortalSalida(int x, int y);
    void createUnit(int id, int key,
                    int x, int y, int toX, int toY, Uint32 t);
    void createTower(int id, int key, int x, int y);
    void createSpell(int key, int x, int y, Uint32 t);
    void createShot(int key, int x, int y, int toX, int toY, Uint32 t);
    void moveUnit(int id, int x, int y, int toX, int toY, Uint32 t);
    void moveUnit(int id, int x, int y, int toX, int toY);
    void setUnitSpeed(int id, Uint32 newSpeed);
    void freezeUnit(int id, Uint32 duration);
    void killUnit(int id);
    TowerView* getTower(int id);

    bool mapLoaded;
    std::mutex mapLoadedMutex;
    std::condition_variable mapLoadedCondVariable;
    void addAnnouncement(std::string announcement);
    void gameOver();
    void win();

    TowerView *onClick(int x, int y);
private:
    void checkIndexDepthLevel(int key);
    void createAnnounce();
};


#endif //TOWERDEFENSE_MODELVIEW_H
