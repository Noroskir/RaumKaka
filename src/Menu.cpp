#include "../include/Menu.h"

void Menu::init(GLFWwindow *pWindow)
{
    m_pWindow = pWindow;

    m_sBackground.create("data/Background.bmp", 0, 0, 800, 600, 800, 600);
}
void Menu::del()
{
    m_pWindow = nullptr;
}
void Menu::handleEvents()
{

}
void Menu::update(float ftime)
{

}
void Menu::render()
{
    m_sBackground.render();
}