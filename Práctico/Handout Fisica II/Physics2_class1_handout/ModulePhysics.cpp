#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment (lib, "Box2D/lib_x86/Debug/Box2D.lib")
#elif 
#pragma comment (lib, "Box2D/lib_x86/Debug/Box2D.lib")

#endif // _DEBUG

#define METER_TO_PIXEL(meter){(int) meter * 100}
#define PIXEL_TO_METER(pixel){(int) pixel * 0.01f}



// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);

	// TODO 4: Create a a big static circle as "ground"
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(5.0f, 5.0f);

	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2CircleShape circle;
	circle.m_p.Set(0.0f, 0.0f);
	circle.m_radius = 3.0f;

	groundBody->CreateFixture(&circle, 0.0f);
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(timeStep, velocityIterations, positionIterations);
	return UPDATE_CONTINUE;
}





// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		

		b2Vec2 gravity(0.0f, 10.0f);
		world = new b2World(gravity);

		// TODO 4: Create a a big static circle as "ground"
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(PIXEL_TO_METER(App->input->GetMouseX()), PIXEL_TO_METER(App->input->GetMouseY()));

		b2Body* groundBody = world->CreateBody(&groundBodyDef);

		b2CircleShape circle;
		circle.m_p.Set(0.0f, 0.0f);
		circle.m_radius = 1.0f;

		groundBody->CreateFixture(&circle, 0.0f);

		PhysBody* pbody = new PhysBody();
		pbody->body = groundBody;
		pbody->width = pbody->height = circle.m_radius;

	}
	
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METER_TO_PIXEL(pos.x), METER_TO_PIXEL(pos.y), METER_TO_PIXEL(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;
	return true;
}
