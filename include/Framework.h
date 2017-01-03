#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shaderprogramm.h"
#include "Sprite.h"
#include "Player.h"


class Framework
{
public:

    Framework();

    void init(int width, int height, const char *title);
    void run();
    void del();

    void handleEvents();
    void update();
    void render();

private:

    void calcTime();

    int m_iWidth;
    int m_iHeight;

    float m_fTime;

    Sprite m_background;

    Player m_player;

    GLFWwindow *m_pWindow;

};

#endif