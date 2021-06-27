#include <core/physicsEngine.hpp>

void PhysicsEngine::init(GLFWwindow* window){
    m_window = window;

    m_world = m_physicsCommon.createPhysicsWorld();
}

void PhysicsEngine::initDebugDrawer(){
    m_world->setIsDebugRenderingEnabled(true);

    reactphysics3d::DebugRenderer m_debugRenderer = m_world->getDebugRenderer();

    m_debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);

    glCreateBuffers(1, &m_VBO);

	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}

void PhysicsEngine::debugRender(glm::mat4& view , glm::mat4& proj, Shader* shader){

    reactphysics3d::DebugRenderer m_debugRenderer = m_world->getDebugRenderer();
    m_debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);

    std::vector<float> m_linesVertices;

    int linesAmount = m_world->getDebugRenderer().getNbLines();
    for(int i = 0; i < linesAmount; i++){
        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point1.x);
        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point1.y);
        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point1.z);

        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point2.x);
        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point2.y);
        m_linesVertices.push_back(m_debugRenderer.getLines()[i].point2.z);
    }

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_linesVertices.size() * sizeof(float), &m_linesVertices, GL_DYNAMIC_DRAW);

    shader->Use();
    shader->setUniform("view", view);
    shader->setUniform("proj", proj);

    glDrawArrays(GL_LINE_STRIP, 0, linesAmount*2);


    std::vector<float> m_trianglesVertices;

    int trianglesAmount = m_debugRenderer.getNbTriangles();
    for(int i = 0; i < trianglesAmount; i++){
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point1.x);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point1.y);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point1.z);

        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point2.x);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point2.y);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point2.z);

        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point3.x);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point3.y);
        m_trianglesVertices.push_back(m_debugRenderer.getTriangles()[i].point3.z);

    }

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_trianglesVertices.size() * sizeof(float), &m_trianglesVertices, GL_DYNAMIC_DRAW);

    shader->Use();
    shader->setUniform("view", view);
    shader->setUniform("proj", proj);

    glDrawArrays(GL_TRIANGLES, 0, trianglesAmount*3);

}

PhysicsEngine::~PhysicsEngine(){
    for(const auto& a : m_colObjects){
        m_world->destroyCollisionBody(a.second->m_body);
        delete a.second;
    }
    m_colObjects.clear();

    m_physicsCommon.destroyPhysicsWorld(m_world);
}

void PhysicsEngine::update(float deltaTime){
    if(m_accumulator > m_timestep){
        m_world->update(m_timestep);
    }
    m_accumulator += deltaTime;
}


void PhysicsEngine::createColObject(std::string name, reactphysics3d::Vector3 position, reactphysics3d::Quaternion rotation){
    reactphysics3d::Vector3 startpos = position;
    reactphysics3d::Quaternion startquat = rotation;

    const reactphysics3d::Transform transform{startpos, startquat};

    collisionObject* colObject = new collisionObject();

    colObject->m_body = m_world->createRigidBody(transform);
    colObject->m_body->setType(reactphysics3d::BodyType::STATIC);

    m_colObjects.insert({name , colObject});
}

void PhysicsEngine::addBoxCollider(std::string name, reactphysics3d::Vector3 scale ,reactphysics3d::Vector3 position, reactphysics3d::Quaternion rotation){
    collisionObject* currObject = m_colObjects.at(name);

    reactphysics3d::BoxShape* boxshape = m_physicsCommon.createBoxShape(scale);

    reactphysics3d::Transform trans = reactphysics3d::Transform::identity();

    currObject->m_col = currObject->m_body->addCollider(boxshape, trans);
}