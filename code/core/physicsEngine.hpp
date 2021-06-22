#ifndef PHYSICSENGINE
#define PHYSICSENGINE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/shader.hpp>

class PhysicsEngine{
private:
	btDefaultCollisionConfiguration* m_colconfig;
	btCollisionDispatcher* m_coldispatch;
	btBroadphaseInterface* m_overlappingpaircache;
	btSequentialImpulseConstraintSolver* m_solver;

	GLFWwindow* m_window;

public:

	btDiscreteDynamicsWorld* m_dynamicsworld;

	PhysicsEngine(){}

	void init(GLFWwindow* window);

	void update(float delta);

};

class PhysicsDebugDrawer : public btIDebugDraw
{
private:
	unsigned int m_VAO;
	unsigned int m_VBO;

	Shader* m_shaderRef;
	glm::mat4* m_viewRef;
	glm::mat4* m_projRef;

	float vertices[6];

public:
	int m_debugmode;

	PhysicsDebugDrawer(Shader* shaderref, glm::mat4* viewRef, glm::mat4* projRef);

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	void reportErrorWarning(const char* warningString);

	void draw3dText(const btVector3& location, const char* textString);

	void setDebugMode(int debugMode);

	int getDebugMode() const;
};

#endif