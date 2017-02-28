#include "../include/Game.h"


void Game::init(GLFWwindow *pWindow)
{
    m_sBackground.create("data/Background.bmp", 0, 0, 800, 600, 800, 600);
    m_Player.init();

    m_AstManager.setShotList(m_Player.getShotList());
    m_pWindow = pWindow;

    m_fTime = 0.0f;
}
void Game::reset()
{
    m_fTime = 0.0f;
}
void Game::exit()
{
    m_sBackground.del();
    m_Player.del();
}
void Game::handleEvents()
{
    if(glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) m_Player.move((float)(-0.3 * m_fTime), 0 );
    if(glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) ==GLFW_PRESS) m_Player.move((float) (0.3 * m_fTime), 0);
    if(glfwGetKey(m_pWindow, GLFW_KEY_SPACE) ==GLFW_PRESS) m_Player.shoot();
    m_AstManager.handleEvents();
}
void Game::update(float fTime)
{
    m_fTime = fTime;
    m_AstManager.update(m_fTime);
    m_Player.update(m_fTime);
}
void Game::render()
{
    m_sBackground.render();
    m_AstManager.render();
    m_Player.render();
}