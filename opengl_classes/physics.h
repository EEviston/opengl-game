#pragma once
#include <windows.h>
#include "btBulletDynamicsCommon.h"
#include <stdio.h>
#include <vector>
using namespace std;
class Physics
{
public:
	Physics();
	std::vector<btRigidBody*> getBodies();
	btRigidBody* addSphere(float rad, float x, float y, float z, float mass_in);
	btDiscreteDynamicsWorld* dynamicsWorld;
	void Free();


private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;/// btAxis3Sweep is an alternative
	btSequentialImpulseConstraintSolver* solver;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	std::vector<btRigidBody*> bodies;



	void init();













};