#include "PhysBody3D.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// TODO 4: Fill in PhysBody methods. Remember to use 
// get/setOpenGLMatrix methods

// ---------------------------------------------------------
PhysBody3D::PhysBody3D(btRigidBody* body)
{

}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	btTransform transform = body->getWorldTransform();
	transform.getOpenGLMatrix(matrix);

}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	btTransform transform = body->getWorldTransform();
	transform.setFromOpenGLMatrix(matrix);
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	mat4x4 mat;

	mat.translate(x, y, z);

	btTransform  translate = body->getWorldTransform();

	//TODO
}
