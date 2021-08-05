#ifndef CAMERAPATHLOADER
#define CAMERAPTHLOADER

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct cameraTargetObject{
    glm::vec3 cameraPos;
    glm::vec3 cameraLookAt;
    float movementSpeed;
    float movementTime; 
};

std::vector<cameraTargetObject> loadCameraPath(const char* filepath);

#endif