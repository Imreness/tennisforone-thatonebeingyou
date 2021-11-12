#include <core/framebuffer.hpp>
#include <spdlog/spdlog.h>

float frameVertices[] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

FrameBuffer::FrameBuffer(int renderWidth, int renderHeight,int windowWidth, int windowHeight, Shader* shader)
    : m_shader(shader) , m_windowHeight(windowHeight), m_windowWidth(windowWidth), m_renderWidth(renderWidth), m_renderHeight(renderHeight)
{
    spdlog::debug("Creating frame buffer...");

    glGenFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glGenTextures(1, &m_textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_renderWidth, m_renderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);

    glGenRenderbuffers(1, &m_renderBufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);

    glRenderbufferStorage    (GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, m_renderWidth, m_renderHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        spdlog::error("Couldn't create framebuffer");
        abort();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    unsigned int VBO;

    glCreateBuffers(1, &VBO);

	glCreateVertexArrays(1, &m_vaoId);

	glBindVertexArray(m_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(frameVertices), &frameVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
}

void FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glViewport(0,0, m_renderWidth, m_renderHeight);
}

void FrameBuffer::Render(float brightness)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, m_windowWidth, m_windowHeight);
    m_shader->Use();
    m_shader->setUniform("darkness", brightness);
    glBindVertexArray(m_vaoId);
    glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}