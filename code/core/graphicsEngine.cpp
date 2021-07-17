#include <core/graphicsEngine.hpp>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

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
        Shader* shader = new Shader{vertexName, fragmentName, geoName};
        m_shaders.insert({std::string(shaderName), shader});
    }
    else{
        std::string vertexName("shaders/"); vertexName.append(shaderName); vertexName.append(".vert");
        std::string fragmentName("shaders/"); fragmentName.append(shaderName); fragmentName.append(".frag");
        Shader* shader = new Shader{vertexName, fragmentName};
        m_shaders.insert({std::string(shaderName), shader});
    }
}

Shader* graphicsEngine::getShader(std::string name){
    return m_shaders.at(name); 
}

void graphicsEngine::renderUi(uiManager &ui){
    Shader* uiShader = m_shaders.at("ui");
    glBindVertexArray(m_uiVAO);
    uiShader->Use();

    for (auto &button : ui.m_buttons){
        if(button.first == ui.m_hovered_button){
            ui.m_textures.at(button.second.m_hoverTexture)->Use();
        }
        else{
            ui.m_textures.at(button.second.m_normalTexture)->Use();
        }

        uiShader->setUniform("model", button.second.m_model);
        uiShader->setUniform("mover", button.second.m_mover);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    for (auto &panel : ui.m_panels){
        ui.m_textures.at(panel.second.m_normalTexture)->Use();

        uiShader->setUniform("model", panel.second.m_model);
        uiShader->setUniform("mover", panel.second.m_mover);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void graphicsEngine::renderStart(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3, 0.3 ,0.3 , 1.);
}

void graphicsEngine::renderObjects(DebugCamera* refcam, std::vector<Texture*>& textures,std::unordered_map<std::string, GameObject>& objects, std::string shaderName){
    Shader* currShader = m_shaders.at(shaderName);
    currShader->Use();
    currShader->setUniform("proj", refcam->m_proj);
    currShader->setUniform("view", refcam->m_view);
    for(auto& object : objects){
        if(object.second.m_render){
            currShader->setUniform("model", object.second.m_modelMat);
            textures.at(object.second.m_refModel->m_texID)->Use();
            object.second.m_refModel->render();
        }
   }
}

void graphicsEngine::renderObjects(RailsCamera* refcam, std::vector<Texture*>& textures,std::unordered_map<std::string, GameObject>& objects, std::string shaderName){
    Shader* currShader = m_shaders.at(shaderName);
    currShader->Use();
    currShader->setUniform("proj", refcam->m_proj);
    currShader->setUniform("view", refcam->m_view);
    for(auto& object : objects){
        if(object.second.m_render){
            currShader->setUniform("model", object.second.m_modelMat);
            textures.at(object.second.m_refModel->m_texID)->Use();
            object.second.m_refModel->render();
        }
    }
}

void graphicsEngine::renderObjects(DebugCamera* refcam, std::vector<Texture*>& textures,GameObject& object, std::string shaderName){
    Shader* currShader = m_shaders.at(shaderName);
    currShader->Use();

    currShader->setUniform("proj", refcam->m_proj);
    currShader->setUniform("view", refcam->m_view);
    currShader->setUniform("model", object.m_modelMat);
    textures.at(object.m_refModel->m_texID)->Use();
    object.m_refModel->render();
}

void graphicsEngine::renderObjects(RailsCamera* refcam, std::vector<Texture*>& textures,GameObject& object, std::string shaderName){
    Shader* currShader = m_shaders.at(shaderName);
    currShader->Use();

    currShader->setUniform("proj", refcam->m_proj);
    currShader->setUniform("view", refcam->m_view);
    currShader->setUniform("model", object.m_modelMat);
    textures.at(object.m_refModel->m_texID)->Use();
    object.m_refModel->render();
}

void graphicsEngine::renderEnd(){
    glfwSwapBuffers(m_targetWindow);
    glfwPollEvents();
}

graphicsEngine::~graphicsEngine(){
    spdlog::info("Freeing up graphics engine shaders...");

    glDeleteVertexArrays(1, &m_uiVAO);
    glDeleteBuffers(1, &m_uiVBO);

    for(const auto& thing : m_shaders){
        delete thing.second;
    }
    m_shaders.clear();
}