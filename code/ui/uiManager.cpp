#include <ui/uiManager.hpp>
#include <core/assetLoader.hpp>

void uiManager::setup(std::string name){
    if(name == "mainmenu"){
        assetLoader::loadUiPackage(m_textures, name.c_str());

        m_hovered_button = "";

        {
            uiButton button{m_screenWidth, m_screenHeight, "play_hover", "play_normal"};
            button.scale(glm::vec2(6, 6));
            button.move(glm::vec2(0, 0));
            m_buttons.insert({"play", button});
        }
        {
            uiButton button{m_screenWidth, m_screenHeight, "settings_hover", "settings_normal"};
            button.scale(glm::vec2(6, 6));
            button.move(glm::vec2(0, -0.2));
            m_buttons.insert({"settings", button});
        }
        {
            uiButton button{m_screenWidth, m_screenHeight, "exit_hover", "exit_normal"};
            button.scale(glm::vec2(6, 6));
            button.move(glm::vec2(0, -0.4));
            m_buttons.insert({"exit", button});
        }
        {
            uiPanel panel{m_screenWidth, m_screenHeight, "logo"};
            panel.scale(glm::vec2(6, 4));
            panel.move(glm::vec2(0, 0.3));
            m_panels.insert({"logo", panel});
        }

    }
}

void uiManager::update(int mouseX, int mouseY){
    if(mouseX < 0 || mouseX > m_screenWidth || mouseY < 0 || mouseY > m_screenHeight){
        m_hovered_button = "";
        return;
    }

    int realX = 0, realY = 0;

    realX = -((m_screenWidth/2) - mouseX);
    realY = (m_screenHeight/2) - mouseY;

    for(const auto& button : m_buttons){
        if(button.second.m_topleft.x < realX && button.second.m_topright.x > realX 
            && button.second.m_topleft.y > realY && button.second.m_bottomleft.y < realY){
                m_hovered_button = button.first;
                return;
        }
    }

    m_hovered_button = "";
}

uiManager::~uiManager(){
    for(const auto& thing : m_textures){
        delete thing.second;
    }
    m_textures.clear();
}