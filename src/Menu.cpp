#include "../include/Menu.h"

void Menu::init(GLFWwindow *pWindow)
{
    m_pWindow = pWindow;

    m_sBackground.create("data/Background.bmp", 0, 0, 800, 600, 800, 600);

    m_Text.init();
    m_Text.createText("MENU", Vector2f(300.0f, 50.0f), Vector3f(0.6f, 1.0f, 0.4f), 2.0f);
}
void Menu::del()
{
    m_pWindow = nullptr;
    m_Text.removeText("MENU");
}
void Menu::handleEvents()
{

}
void Menu::update(float ftime)
{
    m_fTime = ftime;
}
void Menu::render()
{
    //m_sBackground.render();
    m_Text.staticRender();
}