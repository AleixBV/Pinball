#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = background = NULL;
	ray_on = false;
	sensed = false;
	show_back = false;
	flip_l = flip_r = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	background = App->textures->Load("pinball/pinball.png");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//--------------------------------
	int pinball_1[52] = {
		675, 692,
		601, 152,
		572, 118,
		529, 91,
		529, 95,
		544, 105,
		568, 123,
		592, 159,
		599, 194,
		591, 254,
		570, 301,
		574, 355,
		569, 383,
		580, 372,
		601, 381,
		591, 400,
		606, 403,
		605, 443,
		616, 439,
		612, 373,
		630, 374,
		664, 643,
		629, 642,
		629, 619,
		577, 661,
		576, 694
	};

	int pinball_2[60] = {
		708, 692,
		641, 184,
		616, 124,
		577, 88,
		530, 65,
		482, 56,
		421, 58,
		379, 72,
		345, 53,
		313, 53,
		288, 69,
		280, 95,
		300, 124,
		273, 160,
		260, 196,
		282, 262,
		277, 293,
		317, 321,
		310, 425,
		246, 439,
		226, 461,
		199, 638,
		236, 641,
		239, 588,
		335, 660,
		334, 693,
		164, 692,
		275, 28,
		630, 29,
		741, 690
	};

	int pinball_3[12] = {
		374, 152,
		414, 134,
		411, 101,
		390, 95,
		369, 112,
		369, 141
	};

	int pinball_4[32] = {
		540, 253,
		565, 222,
		571, 188,
		561, 154,
		540, 134,
		510, 110,
		492, 98,
		492, 125,
		500, 128,
		505, 121,
		517, 129,
		518, 142,
		538, 162,
		547, 187,
		543, 212,
		528, 245
	};

	int pinball_5[20] = {
		304, 176,
		293, 175,
		290, 206,
		297, 234,
		305, 261,
		331, 294,
		377, 266,
		370, 247,
		309, 220,
		301, 202
	};

	int pinball_6[12] = {
		253, 482,
		259, 482,
		254, 536,
		369, 626,
		365, 630,
		247, 538
	};

	int pinball_7[8] = {
		284, 476,
		292, 476,
		288, 521,
		280, 521
	};

	int pinball_8[12] = {
		626, 564,
		620, 477,
		613, 477,
		618, 561,
		534, 627,
		539, 631
	};

	int pinball_9[6] = {
		325, 475,
		315, 551,
		365, 578
	};

	int pinball_10[6] = {
		578, 474,
		588, 548,
		543, 581
	};

	int pinball_11[8] = {
		436, 129,
		436, 101,
		441, 101,
		441, 129
	};

	int pinball_12[8] = {
		464, 129,
		464, 101,
		469, 101,
		469, 129
	};

	int pinball_13[22] = {
		417, 247,
		468, 263,
		474, 242,
		472, 224,
		464, 230,
		454, 234,
		445, 233,
		436, 227,
		432, 221,
		431, 214,
		417, 226
	};
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

	PhysBody* f_r = App->physics->CreatePolygon(0, 0, flipper_r, 12, b2_dynamicBody);
	PhysBody* f_l = App->physics->CreatePolygon(0, 0, flipper_l, 12, b2_dynamicBody);

	App->physics->CreateCircle(331, 97, radius, b2_staticBody);
	App->physics->CreateCircle(421, 173, radius, b2_staticBody);
	App->physics->CreateCircle(453, 216, radius, b2_staticBody);
	App->physics->CreateCircle(486, 161, radius, b2_staticBody);

	PhysBody* c_l = App->physics->CreateCircle(371, 639, 1, b2_staticBody);
	PhysBody* c_r = App->physics->CreateCircle(533, 640, 1, b2_staticBody);

	b2Vec2 fl_pivot(PIXEL_TO_METERS(371), PIXEL_TO_METERS(639));
	b2Vec2 fr_pivot(PIXEL_TO_METERS(533), PIXEL_TO_METERS(640));

	b2RevoluteJointDef joint_fL;
	joint_fL.bodyA = c_l->body;
	joint_fL.bodyB = f_l->body;
	joint_fL.localAnchorA = c_l->body->GetLocalCenter();
	joint_fL.localAnchorB = fl_pivot;
	joint_fL.enableLimit = true;
	joint_fL.lowerAngle = 0;
	joint_fL.upperAngle = 70 * DEGTORAD;
	joint_fL.motorSpeed = -100;
	joint_fL.maxMotorTorque = 100;

	b2RevoluteJointDef joint_fR;
	joint_fR.bodyA = c_r->body;
	joint_fR.bodyB = f_r->body;
	joint_fR.localAnchorA = c_r->body->GetLocalCenter();
	joint_fR.localAnchorB = fr_pivot;
	joint_fR.enableLimit = true;
	joint_fR.lowerAngle = -70 * DEGTORAD;
	joint_fR.upperAngle = 0;
	joint_fR.motorSpeed = 100;
	joint_fR.maxMotorTorque = 100;

	flip_l = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&joint_fL);
	flip_r = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&joint_fR);

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
		App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody);

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		show_back= !show_back;

	if (show_back==true)
		App->renderer->Blit(background, 0, 0);

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		flip_l->EnableMotor(true);

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
		flip_l->EnableMotor(false);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		flip_r->EnableMotor(true);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
		flip_r->EnableMotor(false);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

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
}
