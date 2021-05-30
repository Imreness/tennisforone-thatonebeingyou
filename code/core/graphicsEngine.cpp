#include <core/graphicsEngine.hpp>
#include <glm/glm.hpp>

void graphicsEngine::setTargetWindow(GLFWwindow* window){
    m_targetWindow = window;
}

void graphicsEngine::initUi(){
    //init the UI quad
	glCreateBuffers(1, &m_uiVBO);

	glCreateVertexArrays(1, &m_uiVAO);

	glBindVertexArray(m_uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_uiQuad) , &m_uiQuad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
}

void graphicsEngine::loadShader(const char* shaderName, bool hasGeo){
    if(hasGeo){
        std::string vertexName("shaders/"); vertexName.append(shaderName); vertexName.append(".vert");
        std::string fragmentName("shaders/"); fragmentName.append(shaderName); fragmentName.append(".frag");
        std::string geoName("shaders/"); geoName.append(shaderName); geoName.append(".geo");
        Shader shader{vertexName, fragmentName, geoName};
        m_shaders.insert({std::string(shaderName), shader});
    }
    else{
        std::string vertexName("shaders/"); vertexName.append(shaderName); vertexName.append(".vert");
        std::string fragmentName("shaders/"); fragmentName.append(shaderName); fragmentName.append(".frag");
        Shader shader{vertexName, fragmentName};
        m_shaders.insert({std::string(shaderName), shader});
    }
}

void graphicsEngine::renderUi(uiManager &ui){
    Shader &uiShader = m_shaders.at("ui");
    glBindVertexArray(m_uiVAO);
    uiShader.Use();

    for (auto &button : ui.m_buttons){
        if(button.first == ui.m_hovered_button){
            ui.m_textures.at(button.second.m_hoverTexture).Use();
        }
        else{
            ui.m_textures.at(button.second.m_normalTexture).Use();
        }

        uiShader.setUniform("model", &(button.second.m_model[0][0]));
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void graphicsEngine::renderStart(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.1 ,0.1 , 1.);
}

void graphicsEngine::renderEnd(){
    glfwSwapBuffers(m_targetWindow);
    glfwPollEvents();
}