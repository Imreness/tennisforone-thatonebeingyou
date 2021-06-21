#include <core/physicsEngine.hpp>

void PhysicsEngine::init(GLFWwindow* window){
    m_window = window;

    //Physics setup
	m_colconfig = new btDefaultCollisionConfiguration();
	m_coldispatch = new btCollisionDispatcher(m_colconfig);
	m_overlappingpaircache = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();

	m_dynamicsworld = new btDiscreteDynamicsWorld(m_coldispatch, m_overlappingpaircache, m_solver, m_colconfig);
	m_dynamicsworld->setGravity(btVector3(0, -10, 0));
}