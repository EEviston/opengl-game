#include "physics.h"

Physics::Physics()
{
	init();
}

void Physics::init()
{
	int i;
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase(); 	/// btAxis3Sweep is an alternative
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));


	//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(0), btScalar(0), btScalar(0))); //static plane instead?																										
	btStaticPlaneShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), btScalar(0));
	collisionShapes.push_back(groundShape);	//keep track of the shapes

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));


	btScalar mass(0.);
	bool isDynamic = (mass != 0.f);
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//motionstate provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setFriction(0.9);

	//add le body to the world
	dynamicsWorld->addRigidBody(body);
	bodies.push_back(body);
	printf("physics init done");
}

btRigidBody* Physics::addSphere(float rad, float x, float y, float z, float mass_in)
{
	//create a dynamic rigidbody

	//btCollisionShape* colShape = new btSphereShape(btScalar(1.0));
	btSphereShape* colShape = new btSphereShape(rad);
	collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(x,y,z));

	//btScalar mass (0.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass_in != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		printf("\nDYNAMIC");
		colShape->calculateLocalInertia(mass_in, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass_in, myMotionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	body->setRestitution(0.5);
	body->setFriction(0.0);
	body->setRollingFriction(256.0);

	body->setUserPointer((void*)body->getCollisionShape()->getShapeType());
	
	//next two lines are for setting it to a kinematic body; not sure if we want that
	//body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	//body->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(body);
	bodies.push_back(body);
	return body;
}

std::vector<btRigidBody*> Physics::getBodies()
{
	return bodies;
}

void Physics::Free()
{
	for (int j = 0; j<collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;

	//bodies.clear();
}