#ifndef UIBUTTON
#define UIBUTTON
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct uiButton{
    std::string m_hoverTexture;
    std::string m_normalTexture;

    glm::mat4 m_model;
    glm::vec2 m_scaledMover;
    glm::vec2 m_mover;

    glm::vec2 m_topleft;
    glm::vec2 m_topright;
    glm::vec2 m_bottomleft;
    glm::vec2 m_bottomright;

    int m_screenWidth;
    int m_screenHeight;

    uiButton(int, int, std::string, std::string);

    //note - scaling works in reverse. scaling by 5 , 5 makes it FIFTH of the size.
    void scale(glm::vec2);

    void move(glm::vec2);

};

#endif