#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;
class SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* flipL_tex;
	SDL_Texture* flipR_tex;
	SDL_Texture* ball_tex;

	PhysBody* f_l;
	PhysBody* f_r;
	PhysBody* ball;

private:
	b2RevoluteJoint* flip_l;
	b2RevoluteJoint* flip_r;
	b2PrismaticJoint* quicker;
};