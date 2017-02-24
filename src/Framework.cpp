#include "../include/Framework.h"

Framework::Framework()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    m_fTime = 0.0f;

}

void Framework::init(int width, int height, const char *title)
{
    m_iCurrState = game;

    m_iWidth = width;
    m_iHeight = height;
    m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, title, nullptr, nullptr);

    GLFWwindow *neuerPointer = m_pWindow;

    if(m_pWindow == nullptr)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_pWindow);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init GLEW!" << std::endl;
        glfwTerminate();
    }

    int wid, hei;
    glfwGetFramebufferSize(m_pWindow, &wid, &hei);

    glViewport(0, 0, width, height);
    glClearColor(0, 0, 1, 1);

    //zeit zurücksetzten
    glfwSetTime(0.0f);

    m_Game.init(neuerPointer);
}
void Framework::run()
{
    while(!glfwWindowShouldClose(m_pWindow))
    {
        switch(m_iCurrState)
        {
            case game:
            {
                m_Game.handleEvents();
                m_Game.update(m_fTime);
                m_Game.render();
            }break;
            case menu:
            {
                m_Menu.handleEvents();
                m_Menu.update(m_fTime);
                m_Menu.render();
            }break;
        }
        //framework zeug
        handleEvents();
        update();
        render();
    }
}
void Framework::del()
{
    glfwTerminate();
}
void Framework::handleEvents()
{
    glfwPollEvents();

    if(glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "Curr state: " << m_iCurrState << std::endl;
        m_iCurrState = (m_iCurrState + 1) % 2;
        if(m_iCurrState == menu)
        {
            m_Menu.init(m_pWindow);
        }
        else
        {
            m_Menu.del();
        }

    }
}
void Framework::update()
{
    calcTime();
}
void Framework::render()
{
    glfwSwapBuffers(m_pWindow);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Framework::calcTime()
{
    m_fTime = glfwGetTime();
    glfwSetTime(0.0f);
}