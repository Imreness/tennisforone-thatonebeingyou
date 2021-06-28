#ifndef PHYSICSENGINE
#define PHYSICSENGINE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <reactphysics3d/reactphysics3d.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <core/shader.hpp>

struct collisionObject{
	reactphysics3d::CollisionBody* m_body;
	reactphysics3d::Collider* m_col;
};

struct Raycasthit{
	bool m_isHit;
	std::string m_name;
	glm::vec3 m_hitpos;
};


class PhysicsEngine
{
private:
	GLFWwindow *m_window;

	reactphysics3d::PhysicsCommon m_physicsCommon;
	reactphysics3d::PhysicsWorld* m_world;

	std::unordered_map<std::string, collisionObject*> m_colObjects;

	double m_timestep = 1. / 60.f;
	double m_accumulator = 0;


	//debug drawing stuff
	unsigned int m_VAO;
	unsigned int m_VBO;

	float m_raydebugdata[6] = {0 , 0 , 0 , 0 , 0 , 0};

public:
	PhysicsEngine() {}

	void init(GLFWwindow *window);

	void initDebugDrawer();

	void debugRender(glm::mat4& view , glm::mat4& proj, Shader* shader);

	void update(float deltaTime);

	Raycasthit testMouseRayAgainstCollisionObject(std::string name, glm::mat4& view, glm::mat4& proj, bool setDebugRayData = false);

	void createColObject(std::string, reactphysics3d::Vector3 = reactphysics3d::Vector3{0.,0.,0.}, reactphysics3d::Quaternion = reactphysics3d::Quaternion::identity());
	void addBoxCollider(std::string, reactphysics3d::Vector3 = reactphysics3d::Vector3{1., 1., 1.}  ,reactphysics3d::Vector3 = reactphysics3d::Vector3{0.,0.,0.}, reactphysics3d::Quaternion = reactphysics3d::Quaternion::identity());

	~PhysicsEngine();
};



#endif