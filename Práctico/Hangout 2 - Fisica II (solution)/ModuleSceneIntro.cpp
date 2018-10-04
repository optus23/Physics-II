#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

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
	// TODO 3: Move all creation of bodies on 1,2,3 key press here in the scene
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 100));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[266] = {
			66, 738,
			53, 744,
			41, 753,
			28, 764,
			18, 777,
			12, 789,
			12, 992,
			64, 992,
			64, 969,
			210, 1074,
			336, 1074,
			483, 971,
			483, 994,
			533, 994,
			533, 790,
			530, 775,
			522, 761,
			512, 750,
			502, 744,
			490, 738,
			475, 736,
			475, 628,
			483, 616,
			490, 605,
			495, 595,
			500, 584,
			507, 569,
			513, 555,
			518, 541,
			523, 524,
			528, 507,
			532, 491,
			534, 474,
			536, 460,
			539, 439,
			539, 368,
			538, 350,
			537, 331,
			535, 312,
			533, 293,
			531, 275,
			527, 257,
			524, 241,
			519, 225,
			514, 210,
			510, 198,
			505, 181,
			516, 189,
			524, 201,
			532, 214,
			538, 226,
			543, 237,
			548, 249,
			552, 261,
			556, 272,
			560, 287,
			564, 300,
			565, 309,
			565, 1056,
			601, 1056,
			600, 307,
			599, 295,
			597, 278,
			594, 265,
			590, 251,
			586, 235,
			580, 219,
			574, 203,
			566, 187,
			557, 170,
			546, 155,
			535, 140,
			523, 127,
			510, 114,
			498, 103,
			481, 91,
			462, 78,
			442, 67,
			426, 58,
			408, 51,
			393, 46,
			373, 40,
			349, 36,
			329, 35,
			302, 34,
			279, 34,
			256, 34,
			232, 37,
			214, 40,
			193, 46,
			170, 53,
			157, 60,
			143, 67,
			128, 77,
			114, 87,
			97, 101,
			79, 119,
			69, 131,
			58, 147,
			47, 165,
			39, 182,
			30, 203,
			23, 229,
			19, 251,
			15, 272,
			13, 288,
			10, 309,
			8, 329,
			6, 346,
			5, 375,
			5, 438,
			6, 458,
			7, 468,
			8, 482,
			9, 492,
			11, 503,
			13, 514,
			15, 524,
			18, 535,
			21, 544,
			24, 552,
			26, 560,
			29, 568,
			33, 576,
			36, 584,
			40, 590,
			43, 597,
			47, 603,
			52, 608,
			55, 612,
			60, 618,
			66, 626,
			66, 737
		};

		


		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 266));
	}
	
	// TODO 5: Draw all the circles using "circle" texture
	// Draw all circles
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		//App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}
