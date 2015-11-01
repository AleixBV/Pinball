#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* background;
	SDL_Texture* circle;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	bool check;

private:
	bool show_back;
	b2RevoluteJoint* flip_l;
	b2RevoluteJoint* flip_r;
	b2PrismaticJoint* quicker;
};
