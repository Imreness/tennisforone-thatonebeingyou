#include <ui/uiButton.hpp>

uiButton::uiButton(int screenWidth, int screenHeight,
    std::string hover, std::string normal): m_hoverTexture(hover) , m_normalTexture(normal)
{
    m_model = glm::mat4(1.0);

    m_topright = glm::vec2(screenWidth/2,screenHeight/2);
    m_topleft = glm::vec2(-(screenWidth/2),screenHeight/2);
    m_bottomright = glm::vec2(screenWidth/2,-(screenHeight/2));
    m_bottomleft = glm::vec2(-(screenWidth/2),-(screenHeight/2));
}

void uiButton::scale(glm::vec2 scaler){
    m_model = glm::scale(m_model, glm::vec3(1 / scaler.x, 1 / scaler.y, 1));

    m_topright = m_topright / scaler;
    m_topleft = m_topleft / scaler;
    m_bottomleft = m_bottomleft / scaler;
    m_bottomright = m_bottomright / scaler;
}