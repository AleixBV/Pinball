#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Globals.h"

class PhysBody;
class b2RevoluteJoint;
class b2PrismaticJoint;
class ModuleSceneIntro;

enum SensorType
{
	circle_yellow,
	circle_blue,
	circle_bouncer,
};

struct Sensor
{
	Sensor() : body(NULL), texture(NULL), sound(0), light(false), collision(false)
	{}

	Sensor(ModuleSceneIntro* physics, int x, int y, SensorType type);

	PhysBody* body;
	int x;
	int y;
	SensorType type;
	SDL_Texture* texture;
	uint sound;
	bool light;
	bool collision;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* background;
	SDL_Texture* frontground;
	SDL_Texture* circle;

	SDL_Texture* texture_circle_yellow_sensor;
	SDL_Texture* texture_circle_blue_sensor;
	SDL_Texture* texture_circle_bouncer_sensor;

	uint sound_circle_yellow_sensor;
	uint sound_circle_blue_sensor;
	uint sound_circle_bouncer_sensor;

	uint start_game_sound;

	p2Point<int> ray;
	bool ray_on;
	p2DynArray<Sensor> sensors;

	bool check;

	bool collisioned;//to check if there are collision in last frame

private:
	bool show_back;
};
