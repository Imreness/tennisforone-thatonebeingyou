#include <core/physicsEngine.hpp>

void PhysicsEngine::init(GLFWwindow* window){
    m_window = window;

    m_world = m_physicsCommon.createPhysicsWorld();
}

void PhysicsEngine::initDebugDrawer(){
    m_world->setIsDebugRenderingEnabled(true);

    glCreateBuffers(1, &m_VBO);

	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindVertexArray(0);
}

bool PhysicsEngine::testCollisionBodies(std::string firstbody, std::string secondbody){
    return m_world->testOverlap(m_colObjects.at(firstbody)->m_body, m_colObjects.at(secondbody)->m_body);
}

collisionObject* PhysicsEngine::getColObject(std::string name){
    return m_colObjects.at(name);
}

void PhysicsEngine::debugRender(glm::mat4& view , glm::mat4& proj, Shader* shader){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    reactphysics3d::DebugRenderer m_debugRenderer = m_world->getDebugRenderer();
    m_debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
    m_debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
    m_debugRenderer.setContactPointSphereRadius(5);
    m_debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
    m_debugRenderer.computeDebugRenderingPrimitives(*m_world);

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

    if(m_linesVertices.size() > 0){
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_linesVertices.size() * sizeof(float), &(m_linesVertices.at(0)), GL_DYNAMIC_DRAW);

        shader->Use();
        shader->setUniform("view", view);
        shader->setUniform("proj", proj);

        glDrawArrays(GL_LINE_STRIP, 0, linesAmount*2);
    }

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &(m_raydebugdata[0]), GL_DYNAMIC_DRAW);

    shader->Use();
    shader->setUniform("view", view);
    shader->setUniform("proj", proj);

    glDrawArrays(GL_LINE_STRIP, 0, 2 );   

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

    if(m_trianglesVertices.size() > 0){
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_trianglesVertices.size() * sizeof(float), &(m_trianglesVertices.at(0)), GL_DYNAMIC_DRAW);

    	glEnableVertexAttribArray(0);
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

        shader->Use();
        shader->setUniform("view", view);
        shader->setUniform("proj", proj);

        glDrawArrays(GL_TRIANGLES, 0, trianglesAmount*3);    
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

Raycasthit PhysicsEngine::testMouseRayAgainstCollisionObject(std::string name, glm::mat4& view, glm::mat4& proj, bool setDebugRayData){
    collisionObject* currObject = m_colObjects.at(name);

    int windowWidth, windowHeight; 
    double mouseX, mouseY;

    glfwGetCursorPos(m_window, &mouseX, &mouseY);
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	//Get the mouse as Normalized Device coordinates (clamped between 0 and 1)
	glm::vec4 RayStart_NDC(
		(mouseX / windowWidth - 0.5f) * 2.f,
		((mouseY / windowHeight - 0.5f) * 2.f) * -1.f,
		-1.f,
		1.f
	);
	glm::vec4 RayEnd_NDC(
		(mouseX / windowWidth - 0.5f) * 2.f,
		((mouseY / windowHeight - 0.5f) * 2.f) * -1.f,
		0.f,
		1.f
	);

	
	//When we multiply the NDC values with M (Projection and View), we reverse the application of said matrixes,
	//So we get the proper World values of the cursor
	glm::mat4 M = glm::inverse(proj * view);

	glm::vec4 RayStart_world = M * RayStart_NDC; RayStart_world /= RayStart_world.w;
	glm::vec4 RayEnd_world   = M * RayEnd_NDC  ; RayEnd_world  /= RayEnd_world.w;

    glm::vec3 raydirection(RayEnd_world - RayStart_world);
    raydirection = glm::normalize(raydirection);
    


    reactphysics3d::Vector3 rayStart(RayStart_world.x, RayStart_world.y, RayStart_world.z);
    reactphysics3d::Vector3 rayEnd(raydirection.x * 500, raydirection.y * 500, raydirection.z * 500);

    if(setDebugRayData){
       m_raydebugdata[0] = rayStart.x;
       m_raydebugdata[1] = rayStart.y;
       m_raydebugdata[2] = rayStart.z;
       m_raydebugdata[3] = rayEnd.x;
       m_raydebugdata[4] = rayEnd.y;
       m_raydebugdata[5] = rayEnd.z;
    }

    reactphysics3d::Ray ray(rayStart, rayEnd);

    Raycasthit raycastinfo;
    reactphysics3d::RaycastInfo info;

    raycastinfo.m_isHit = currObject->m_col->raycast(ray, info);

    if(raycastinfo.m_isHit){
        raycastinfo.m_hitpos = glm::vec3(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
    }
    
    return raycastinfo;
}

Raycasthit PhysicsEngine::testRayAgainstCollisionObject(std::string name, glm::vec3 position, glm::vec3 direction, bool setDebugRayData){

    reactphysics3d::Vector3 rayStart(position.x, position.y, position.z);
    reactphysics3d::Vector3 rayEnd(direction.x * 500, direction.y * 500, direction.z * 500);

    if(setDebugRayData){
       m_raydebugdata[0] = rayStart.x;
       m_raydebugdata[1] = rayStart.y;
       m_raydebugdata[2] = rayStart.z;
       m_raydebugdata[3] = rayEnd.x;
       m_raydebugdata[4] = rayEnd.y;
       m_raydebugdata[5] = rayEnd.z;
    }

    reactphysics3d::Ray ray(rayStart, rayEnd);

    Raycasthit raycastinfo;
    reactphysics3d::RaycastInfo info;

    collisionObject* currObject = m_colObjects.at(name);

    raycastinfo.m_isHit = currObject->m_col->raycast(ray, info);

    if(raycastinfo.m_isHit){
        raycastinfo.m_hitpos = glm::vec3(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
    }
    
    return raycastinfo;
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

    reactphysics3d::Transform trans = reactphysics3d::Transform(position, rotation);

    currObject->m_col = currObject->m_body->addCollider(boxshape, trans);
}

void PhysicsEngine::addSphereCollider(std::string name, float radius, reactphysics3d::Vector3 position, reactphysics3d::Quaternion rotation){
    collisionObject* currObject = m_colObjects.at(name);

    reactphysics3d::SphereShape* shape = m_physicsCommon.createSphereShape(radius);

    reactphysics3d::Transform trans = reactphysics3d::Transform(position, rotation);

    currObject->m_col = currObject->m_body->addCollider(shape, trans);
}

void PhysicsEngine::setTransform(std::string name,reactphysics3d::Vector3 pos, reactphysics3d::Quaternion rot){
    collisionObject* currObject = m_colObjects.at(name);

    currObject->m_body->setTransform(reactphysics3d::Transform(pos, rot));
}

void PhysicsEngine::setTransformFromMat(std::string name, glm::mat4& mat){
    glm::vec3 scale;
    glm::quat rot;
    glm::vec3 pos;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(mat, scale, rot, pos, skew, perspective);

    setTransform(name, reactphysics3d::Vector3(pos.x, pos.y, pos.z), reactphysics3d::Quaternion(rot.x, rot.y, rot.z, rot.w));
}