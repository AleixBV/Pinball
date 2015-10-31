#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{
	flip_l = flip_r = NULL;
	quicker = NULL;
	flipL_tex = flipR_tex = ball_tex = NULL;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	flipL_tex = App->textures->Load("pinball/flip_es.png");
	flipR_tex = App->textures->Load("pinball/flip_dr.png");
	ball_tex = App->textures->Load("pinball/ball.png");

	//Flippers
	//--------------------------------
	int flipper_l[12] = {
		427, 607,
		426, 601,
		418, 600,
		362, 636,
		361, 648,
		372, 653
	};

	int flipper_r[12] = {
		534, 651,
		543, 648,
		543, 638,
		488, 602,
		481, 602,
		482, 609
	};
	//-------------------------------
	f_r = App->physics->CreatePolygon(0, 0, flipper_r, 12, b2_dynamicBody, 2.0f);
	f_l = App->physics->CreatePolygon(0, 0, flipper_l, 12, b2_dynamicBody, 2.0f);

	PhysBody* c_l = App->physics->CreateCircle(371, 639, 1, b2_staticBody);
	PhysBody* c_r = App->physics->CreateCircle(533, 640, 1, b2_staticBody);

	b2Vec2 fl_pivot(PIXEL_TO_METERS(371), PIXEL_TO_METERS(639));
	b2Vec2 fr_pivot(PIXEL_TO_METERS(533), PIXEL_TO_METERS(640));

	flip_l = App->physics->CreateRevoluteJoint(c_l, f_l, c_l->body->GetLocalCenter(), fl_pivot, true, 0, 70, -200, 100);
	flip_r = App->physics->CreateRevoluteJoint(c_r, f_r, c_r->body->GetLocalCenter(), fr_pivot, true, -70, 0, 200, 100);

	//Quicker
	int quicker_b[8] = {
		676, 638,
		697, 635,
		703, 681,
		683, 684
	};

	PhysBody* quicker_box = App->physics->CreatePolygon(0, 0, quicker_b, 8, b2_dynamicBody, 1.0f);
	PhysBody* quick_point = App->physics->CreateCircle(670, 550, 10, b2_staticBody, 0, true);

	quicker = App->physics->CreatePrismaticJoint(quick_point, quicker_box);

	//Ball
	ball = App->physics->CreateCircle(677, 600, 10, b2_dynamicBody);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Render flippers
	App->renderer->Blit(flipL_tex, 360, 600, NULL, 1.0f, f_l->GetRotation(), 12, 39);
	App->renderer->Blit(flipR_tex, 475, 600, NULL, 1.0f, f_r->GetRotation(), 56, 41);

	//Render the ball
	int ball_x, ball_y;
	ball->GetPosition(ball_x, ball_y);
	App->renderer->Blit(ball_tex, ball_x, ball_y, NULL, 1.0f, ball->GetRotation());

	return UPDATE_CONTINUE;
}



