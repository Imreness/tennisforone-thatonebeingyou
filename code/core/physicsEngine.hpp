#ifndef PHYSICSENGINE
#define PHYSICSENGINE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <btBulletDynamicsCommon.h>

class PhysicsEngine{
private:
	btDefaultCollisionConfiguration* m_colconfig;
	btCollisionDispatcher* m_coldispatch;
	btBroadphaseInterface* m_overlappingpaircache;
	btSequentialImpulseConstraintSolver* m_solver;

	btDiscreteDynamicsWorld* m_dynamicsworld;

	GLFWwindow* m_window;

public:

};

#endif