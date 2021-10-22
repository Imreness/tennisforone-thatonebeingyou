#ifndef FRAMEBUFFEROBJECT
#define FRAMEBUFFEROBJECT

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <core/shader.hpp>

//Sidenote:
//Originally the game was supposed to be pixelated a bit to mimic the lower resolution of late 90's 3D games.
//Ultimately ended up dropping  that idea, but the function still remains in the code! 

//Dead simple FrameBuffer class. Has custom render resolution functionalities.
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
    void Render(float brightness = 1.0f);

};

#endif