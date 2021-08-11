#include <objects/gameObject.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

GameObject::GameObject(Model* refModel, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotation)
    :m_refModel(refModel), m_modelMat{1.}{
    glm::vec3 refscale;
    glm::quat refrot;
    glm::vec3 refpos;
    glm::vec3 refskew;
    glm::vec4 refperspective;

    glm::decompose(refModel->m_initTransform, refscale, refrot, refpos, refskew, refperspective);

    m_modelMat = glm::translate(m_modelMat, translate + refpos);
    m_modelMat = glm::scale(m_modelMat, scale * refscale);

    glm::mat4 rotmatrix = glm::mat4(1.f);
    rotmatrix = glm::toMat4(refrot);

    m_modelMat = glm::rotate(m_modelMat, rotation.x , glm::vec3(1, 0 ,0));
    m_modelMat = glm::rotate(m_modelMat, rotation.y , glm::vec3(0, 1 ,0));
    m_modelMat = glm::rotate(m_modelMat, rotation.z , glm::vec3(0, 0 ,1));

    m_modelMat *= rotmatrix;
}