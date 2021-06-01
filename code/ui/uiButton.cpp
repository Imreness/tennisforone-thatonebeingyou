#include <ui/uiButton.hpp>

uiButton::uiButton(int screenWidth, int screenHeight,
    std::string hover, std::string normal): m_hoverTexture(hover) , m_normalTexture(normal), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
    m_model = glm::mat4(1.0);
    m_mover = glm::vec2(0);

    m_topright = glm::vec2(screenWidth/2,screenHeight/2);
    m_topleft = glm::vec2(-(screenWidth/2),screenHeight/2);
    m_bottomright = glm::vec2(screenWidth/2,-(screenHeight/2));
    m_bottomleft = glm::vec2(-(screenWidth/2),-(screenHeight/2));
}

void uiButton::scale(glm::vec2 scaler){
    m_model = glm::scale(m_model, glm::vec3(1 / scaler.x, 1 / scaler.y, 1));
    m_scaledMover = scaler;

    m_topright      = m_topright    / scaler;
    m_topleft       = m_topleft     / scaler;
    m_bottomleft    = m_bottomleft  / scaler;
    m_bottomright   = m_bottomright / scaler;
}

void uiButton::move(glm::vec2 mover){
    m_mover = glm::vec2(mover.x * (m_scaledMover.x * 2), mover.y * (m_scaledMover.y * 2));

    m_topright      = m_topright    + glm::vec2(mover.x * (m_screenWidth), mover.y * (m_screenHeight));
    m_topleft       = m_topleft     + glm::vec2(mover.x * (m_screenWidth), mover.y * (m_screenHeight));
    m_bottomleft    = m_bottomleft  + glm::vec2(mover.x * (m_screenWidth), mover.y * (m_screenHeight));
    m_bottomright   = m_bottomright + glm::vec2(mover.x * (m_screenWidth), mover.y * (m_screenHeight));
}