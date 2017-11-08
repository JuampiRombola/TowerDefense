#ifndef __PROJECTILE_FIRED_GAME_NOTIFICATION__
#define __PROJECTILE_FIRED_GAME_NOTIFICATION__

#include "../ViewModels/ProjectileVM.h"
#include "../GameNotifications/GameNotification.h"

class ProjectileFiredGameNotification : public GameNotification
{
public:
    ProjectileFiredGameNotification(ProjectileVM& vm);
	~ProjectileFiredGameNotification();
	void NotifyUnits(std::vector<UnitView*>& units, TextureLoader &textures,
                 Renderer &renderer);
    void NotifyShots(std::vector<ShotView*>& shots, TextureLoader&textures,
                 Renderer &renderer);
	ProjectileVM vm;
};

#endif
