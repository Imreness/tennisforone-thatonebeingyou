#ifndef UIPANEL
#define UIPANEL
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct uiPanel{
    std::string m_normalTexture;

    glm::mat4 m_model;
    glm::vec2 m_scaledMover;
    glm::vec2 m_mover;

    int m_screenWidth;
    int m_screenHeight;

    uiPanel(int, int, std::string);

    //note - scaling works in reverse. scaling by 5 , 5 makes it FIFTH of the size.
    void scale(glm::vec2);

    void move(glm::vec2);

    ~uiPanel();

};

#endif