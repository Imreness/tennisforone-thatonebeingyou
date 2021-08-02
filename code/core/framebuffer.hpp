#ifndef FRAMEBUFFEROBJECT
#define FRAMEBUFFEROBJECT

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <core/shader.hpp>

class FrameBuffer
{
private:
    unsigned int m_id;
    Shader* m_shader;
    unsigned int m_vaoId;

    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    unsigned int m_renderWidth;
    unsigned int m_renderHeight;
    
    unsigned int m_textureColorBuffer;
    unsigned int m_renderBufferObject;

public:
    FrameBuffer(int renderWidth, int renderHeight,int windowWidth, int windowHeight, Shader* shader);

    void Bind();
    void Unbind();
    void Render();

};

#endif