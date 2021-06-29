#ifndef GAMEOBJECT
#define GAMEOBJECT
#include <core/model.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct GameObject{
    glm::mat4 m_modelMat;

    bool m_render = true;

    Model* m_refModel;

    GameObject(Model* refModel, glm::vec3 translate = glm::vec3(0.), glm::vec3 scale = glm::vec3(1.), glm::vec3 rotation = glm::vec3(0.));
};

#endif