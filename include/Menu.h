#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Sprite.h"
#include "Text.h"


class Menu
{
public:

    void init(GLFWwindow *pWindow);
    void del();

    void handleEvents();
    void update(float ftime);
    void render();

private:

    GLFWwindow *m_pWindow;

    float m_fTime;

    Sprite m_sBackground;
    Text m_Text;
};


#endif