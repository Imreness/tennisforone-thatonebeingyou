#include <objects/gameObject.hpp>

GameObject::GameObject(Model* refModel, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotation)
    :m_refModel(refModel), m_modelMat{1.}{
    
    m_modelMat = glm::translate(m_modelMat, translate);
    m_modelMat = glm::scale(m_modelMat, scale);

    m_modelMat = glm::rotate(m_modelMat, rotation.x , glm::vec3(1, 0 ,0));
    m_modelMat = glm::rotate(m_modelMat, rotation.y , glm::vec3(0, 1 ,0));
    m_modelMat = glm::rotate(m_modelMat, rotation.z , glm::vec3(0, 0 ,1));
}