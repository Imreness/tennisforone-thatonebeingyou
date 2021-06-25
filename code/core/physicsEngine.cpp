#include <core/physicsEngine.hpp>

void PhysicsEngine::init(GLFWwindow* window){
    m_window = window;
}

void PhysicsEngine::update(float delta){
}




//PhysicsDebugDrawer::PhysicsDebugDrawer(Shader* shaderref, glm::mat4* viewRef, glm::mat4* projRef)
//	: m_shaderRef(shaderref), m_viewRef(viewRef), m_projRef(projRef)
//{
//
//	glCreateBuffers(1, &m_VBO);
//
//	glCreateVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &vertices, GL_DYNAMIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
//}
//
//void PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color){
//	for (int x = 0; x < 3; x++)
//	{
//		vertices[x] = from[x];
//	}
//	for (int x = 0; x < 3; x++)
//	{
//		vertices[x + 3] = to[x];
//	}
//
//
//	glBindVertexArray(m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &vertices, GL_DYNAMIC_DRAW);
//
//	glm::mat4 mat = glm::mat4(1.f);
//	m_shaderRef->Use();
//	m_shaderRef->setUniform("proj", *m_projRef);
//	m_shaderRef->setUniform("view", *m_viewRef);
//	m_shaderRef->setUniform("model", mat);
//	glm::vec3 colorvec(color.x(), color.y(), color.z()); 
//	m_shaderRef->setUniform("color", colorvec);
//
//	glDrawArrays(GL_LINE_STRIP, 0, 2);
//}
//
//void PhysicsDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){
//}
//
//void PhysicsDebugDrawer::reportErrorWarning(const char* warningString){
//}
//
//void PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString){
//}
//
//void PhysicsDebugDrawer::setDebugMode(int debugMode){
//	m_debugmode = debugMode;
//}
//
//int PhysicsDebugDrawer::getDebugMode() const{
//	return m_debugmode;
//}