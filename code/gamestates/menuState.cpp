#include <gamestates/menuState.hpp>

void menuState::init(GLFWwindow* referencewindow){
    m_window = referencewindow;
}

void menuState::process(){
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1, 0.1 ,0.1 , 1.);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();

}

void menuState::cleanup(){

}

bool menuState::shouldRun(){
    return !glfwWindowShouldClose(m_window);
}