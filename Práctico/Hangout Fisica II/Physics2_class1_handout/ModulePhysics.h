#pragma once
#include "Module.h"
#include "Globals.h"

struct b2World;

class PhysBody
{
public:
	void GetPosition(int& x, int &y) const;
	float GetRotation() const;

public:
	int width, height;
	b2Body* body;
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	b2World * world;
	bool debug;
};