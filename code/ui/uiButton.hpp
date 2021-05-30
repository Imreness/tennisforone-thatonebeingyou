#ifndef UIBUTTON
#define UIBUTTON
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct uiButton{
    std::string m_hoverTexture;
    std::string m_normalTexture;

    glm::mat4 m_model;

    glm::vec2 m_topleft;
    glm::vec2 m_topright;
    glm::vec2 m_bottomleft;
    glm::vec2 m_bottomright;

    uiButton(int, int, std::string, std::string);

    void scale(glm::vec2);

    void move(glm::vec2);

};

#endif