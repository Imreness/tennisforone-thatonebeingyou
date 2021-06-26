#include <core/physicsEngine.hpp>

void PhysicsEngine::init(GLFWwindow* window){
    m_window = window;

    m_world = m_physicsCommon.createPhysicsWorld();
}

PhysicsEngine::~PhysicsEngine(){
    for(const auto& a : m_colObjects){
        m_world->destroyCollisionBody(a.second->m_body);
        delete a.second;
    }
    m_colObjects.clear();

    m_physicsCommon.destroyPhysicsWorld(m_world);
}


void PhysicsEngine::createColObject(std::string name, reactphysics3d::Vector3 position, reactphysics3d::Quaternion rotation){
    reactphysics3d::Vector3 startpos = position;
    reactphysics3d::Quaternion startquat = rotation;

    const reactphysics3d::Transform transform{startpos, startquat};

    collisionObject* colObject = new collisionObject();

    colObject->m_body = m_world->createCollisionBody(transform);

    m_colObjects.insert({name , colObject});
}

void PhysicsEngine::addBoxCollider(std::string name, reactphysics3d::Vector3 scale ,reactphysics3d::Vector3 position, reactphysics3d::Quaternion rotation){
    collisionObject* currObject = m_colObjects.at(name);

    reactphysics3d::BoxShape* boxshape = m_physicsCommon.createBoxShape(scale);

    reactphysics3d::Transform trans = reactphysics3d::Transform::identity();

    currObject->m_col = currObject->m_body->addCollider(boxshape, trans);
}