#ifndef MENU_H
#define MENU_H

#import <iostream>
#import <GL/glew.h>
#import <GLFW/glfw3.h>

#include "Sprite.h"


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
};


#endif