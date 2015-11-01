#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = frontground = NULL;
	ray_on = false;
	sensed = false;
	show_back = false;
	check = false;
	collisioned = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	frontground = App->textures->Load("pinball/frontground.png");
	background = App->textures->Load("pinball/windows_pinball.png");

	start_game_sound = App->audio->LoadFx("pinball/SOUND1.wav");
	App->audio->PlayFx(start_game_sound);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//--------------------------------
	int pinball_1[52] = {
		575, 121,
		559, 109,
		537, 96,
		511, 88,
		513, 92,
		536, 99,
		558, 112,
		584, 138,
		593, 153,
		603, 181,
		604, 213,
		575, 292,
		576, 365,
		567, 387,
		577, 370,
		600, 380,
		590, 400,
		602, 402,
		609, 437,
		614, 436,
		605, 337,
		618, 250,
		614, 198,
		610, 168,
		599, 148,
		588, 135
	};

	int pinball_2[60] = {
		715, 692,
		641, 181,
		613, 124,
		573, 91,
		530, 66,
		480, 58,
		418, 58,
		373, 67,
		352, 50,
		313, 51,
		284, 65,
		278, 90,
		299, 116,
		271, 159,
		262, 193,
		267, 250,
		275, 298,
		311, 324,
		310, 421,
		246, 439,
		219, 466,
		195, 640,
		233, 640,
		240, 591,
		328, 660,
		328, 691,
		164, 692,
		275, 28,
		630, 29,
		741, 690
	};

	int pinball_3[12] = {
		367, 131,
		410, 118,
		409, 98,
		396, 91,
		388, 93,
		366, 111
	};

	int pinball_4[32] = {
		539, 244,
		564, 213,
		567, 188,
		557, 156,
		540, 134,
		505, 111,
		492, 116,
		500, 121,
		501, 129,
		505, 121,
		517, 129,
		517, 140,
		522, 136,
		546, 157,
		552, 191,
		530, 236
	};

	int pinball_5[20] = {
		301, 173,
		294, 172,
		290, 206,
		297, 234,
		308, 259,
		331, 282,
		371, 255,
		366, 248,
		307, 221,
		300, 203
	};

	int pinball_6[12] = {
		250, 498,
		255, 498,
		254, 537,
		368, 626,
		366, 628,
		248, 537
	};

	int pinball_7[8] = {
		284, 479,
		290, 479,
		286, 520,
		281, 520
	};

	int pinball_8[12] = {
		626, 562,
		619, 479,
		615, 479,
		621, 561,
		540, 624,
		543, 626
	};

	int pinball_9[6] = {
		325, 481,
		319, 550,
		357, 576
	};

	int pinball_10[6] = {
		580, 482,
		585, 550,
		547, 573
	};

	int pinball_11[8] = {
		436, 114,
		436, 101,
		440, 101,
		440, 114
	};

	int pinball_12[8] = {
		464, 115,
		464, 101,
		469, 101,
		469, 115
	};

	int pinball_13[22] = {
		420, 230,
		465, 243,
		471, 241,
		472, 224,
		464, 230,
		454, 234,
		445, 233,
		436, 227,
		432, 221,
		431, 214,
		420, 224
	};

	int pinball_14[16] = {
		576, 691,
		576, 661,
		625, 622,
		629, 639,
		665, 638,
		630, 367,
		633, 340,
		677, 692
	};

	//--------------------------------

	int radius = 15;

	App->physics->CreateChain(0, 0, pinball_1, 52, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_2, 60, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_3, 12, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_4, 32, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_5, 20, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_6, 12, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_7, 8, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_8, 12, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_9, 6, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_10, 6, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_11, 8, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_12, 8, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_13, 22, b2_staticBody);
	App->physics->CreateChain(0, 0, pinball_14, 16, b2_staticBody);

	App->physics->CreateCircle(331, 97, radius, b2_staticBody, 1.5f);
	App->physics->CreateCircle(421, 180, radius, b2_staticBody, 1.5f);
	App->physics->CreateCircle(453, 225, radius, b2_staticBody, 1.5f);
	App->physics->CreateCircle(486, 170, radius, b2_staticBody, 1.5f);

	//bounds
	int bound_1[8] = {
		324, 477,
		328, 479,
		360, 572,
		358, 576
	};

	int bound_2[8] = {
		581, 481,
		574, 482,
		545, 572,
		549, 575
	};

	App->physics->CreateChain(0, 0, bound_1, 8, b2_staticBody, 0.0f, 1.5f);
	App->physics->CreateChain(0, 0, bound_2, 8, b2_staticBody, 0.0f, 1.5f);

	int bound_3[6] = {
		573, 365,
		570, 318,
		575, 315
	};

	App->physics->CreateChain(0, 0, bound_3, 6, b2_staticBody, 0.0f, 1.5f);

	int bound_4[6] = {
		319, 417,
		320, 372,
		314, 372
	};

	App->physics->CreateChain(0, 0, bound_4, 6, b2_staticBody, 0.0f, 1.5f);


	//Create a box so the ball at the begining doesn't fall
	PhysBody* box = App->physics->CreateRectangle(695, 637, 17, 1, b2_staticBody);
	box->SetPosition(695, 637, -5.0f);

	//sensors for score
	texture_circle_yellow_sensor = App->textures->Load("pinball/light_yellow.png");
	sound_circle_yellow_sensor = App->audio->LoadFx("pinball/SOUND8.wav");

	texture_circle_blue_sensor = App->textures->Load("");
	sound_circle_blue_sensor = App->audio->LoadFx("pinball/SOUND16");

	texture_circle_bouncer_sensor = App->textures->Load("");
	sound_circle_bouncer_sensor = App->audio->LoadFx("pinball/SOUND12.wav");

	sensors.PushBack(Sensor(this, 418, 101, SensorType::circle_yellow));


	//test
	sensors.PushBack(Sensor(this, 660, 460, SensorType::circle_yellow));
	sensors.PushBack(Sensor(this, 660, 450, SensorType::circle_yellow));


	//sensor for lose the game
	sensor = App->physics->CreateRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50, b2_staticBody, 0.0f, true);
	sensor->listener = this;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

//reinitialize for check collisions
update_status ModuleSceneIntro::PreUpdate()
{
	if (collisioned == false)
	{
		for (uint i = 0; i < sensors.Count(); i++)
		{
			if (sensors[i].collision == true)
					sensors[i].collision = false;
		}
	}

	collisioned = false;

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
		App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody, false, 0);

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		show_back = !show_back;

	if (show_back == true)
	{
		App->renderer->Blit(background, 0, 0);

		for (uint i = 0; i < sensors.Count(); i++)
		{
			if (sensors[i].light == true)
				App->renderer->Blit(sensors[i].texture, sensors[i].x, sensors[i].y);
		}

		App->renderer->Blit(App->player->flipL_tex, 360, 600, NULL, 1.0f, App->player->f_l->GetRotation(), 12, 39);
		App->renderer->Blit(App->player->flipR_tex, 475, 600, NULL, 1.0f, App->player->f_r->GetRotation(), 56, 41);

		//Render the ball
		int ball_x, ball_y;
		App->player->ball->GetPosition(ball_x, ball_y);
		int quicker_x, quicker_y;
		App->player->quicker_box->GetPosition(quicker_x, quicker_y);

		App->renderer->Blit(App->player->ball_tex, ball_x, ball_y, NULL, 1.0f);
		App->renderer->Blit(App->player->quicker_tex, quicker_x + 676, quicker_y + 647);
		App->renderer->Blit(frontground, 0, 0);

	}


	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	/*p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
	int x, y;
	c->data->GetPosition(x, y);
	if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
	App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
	c = c->next;
	}

	c = boxes.getFirst();
	*/


	// ray -----------------
	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		App->player->flip_l->EnableMotor(true);

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
		App->player->flip_l->EnableMotor(false);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		App->player->flip_r->EnableMotor(true);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
		App->player->flip_r->EnableMotor(false);

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->player->quicker->EnableMotor(true);

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
		App->player->quicker->EnableMotor(false);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
	

	if (sensor->body == bodyA->body && check != true)
	{
		check = true;
		App->player->life--;

		if (bodyB == App->player->ball)
		{
			/*b2Vec2 speed(0, 0);
			App->player->ball->body->SetLinearVelocity(speed);
			App->player->ball->body->SetAngularVelocity(0.0f);*/
			//TODO: Set respawn point
			//App->player->ball->SetPosition(0, 0);
		}
	}

	for (uint i = 0; i < sensors.Count(); i++)
	{
		if (bodyA == sensors[i].body)
		{
			if (sensors[i].collision == false)
			{
				App->audio->PlayFx(sensors[i].sound); 
				sensors[i].collision = true;

				sensors[i].light = !sensors[i].light;

				switch (sensors[i].type)
				{
				case circle_yellow:
					App->player->score += 20;
					break;

				case circle_blue:
					App->player->score += 10;
					break;

				case circle_bouncer:
					App->player->score += 25;
					break;

				}
			}
		}
	}
	collisioned = true;
}

//function for create sensors for score
Sensor::Sensor(ModuleSceneIntro* scene, int x, int y, SensorType type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	light = false;
	collision = false;
	int radius = 0;

	switch (type)
	{
	case circle_yellow:
		radius = 7;
		texture = scene->texture_circle_yellow_sensor;
		sound = scene->sound_circle_yellow_sensor;
		break;

	case circle_blue:
		radius = 7;
		texture = scene->texture_circle_blue_sensor;
		sound = scene->sound_circle_blue_sensor;
		break;

	case circle_bouncer:
		int radius = 15;
		texture = scene->texture_circle_bouncer_sensor;
		sound = scene->sound_circle_bouncer_sensor;
		break;
	}

	body = scene->App->physics->CreateCircle(x + radius, y + radius, radius, b2_staticBody, 0.0f, false, true);
	body->listener = scene;
}
