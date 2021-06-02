#include <ui/uiPanel.hpp>

uiPanel::uiPanel(int screenWidth, int screenHeight,
    std::string normal): m_normalTexture(normal), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
    m_model = glm::mat4(1.0);
    m_mover = glm::vec2(0);
}

void uiPanel::scale(glm::vec2 scaler){
    m_model = glm::scale(m_model, glm::vec3(1 / scaler.x, 1 / scaler.y, 1));
    m_scaledMover = scaler;
}

void uiPanel::move(glm::vec2 mover){
    m_mover = glm::vec2(mover.x * (m_scaledMover.x * 2), mover.y * (m_scaledMover.y * 2));
}

uiPanel::~uiPanel(){
}