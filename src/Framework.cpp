#include "../include/Framework.h"

Framework::Framework()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

}

void Framework::init(int width, int height, const char *title)
{
    m_iWidth = width;
    m_iHeight = height;
    m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, title, nullptr, nullptr);

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

    m_background.create("data/Background.bmp", 0, 0, 800, 600, 800, 600);

    m_player.init(&m_fTime);

    //zeit zurücksetzten
    glfwSetTime(0.0f);

    ast.init(300, 300);

}
void Framework::run()
{
    while(!glfwWindowShouldClose(m_pWindow))
    {

        handleEvents();
        update();
        render();
    }
}
void Framework::del()
{
    m_background.del();
    m_player.del();
    ast.del();

    glfwTerminate();
}
void Framework::handleEvents()
{
    glfwPollEvents();
    if(glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) m_player.move(-0.3 * m_fTime, 0 );
    if(glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) ==GLFW_PRESS) m_player.move( 0.3 * m_fTime, 0);
    if(glfwGetKey(m_pWindow, GLFW_KEY_SPACE) ==GLFW_PRESS) m_player.shoot();
}
void Framework::update()
{
    calcTime();

    m_player.update(m_fTime);
    ast.update(m_fTime);
}
void Framework::render()
{
    m_background.render();
    m_player.render();
    ast.render();
    glfwSwapBuffers(m_pWindow);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Framework::calcTime()
{
    m_fTime = glfwGetTime();
    glfwSetTime(0.0f);
}