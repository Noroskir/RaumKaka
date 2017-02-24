#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Player.h"
#include "Asteroidenmanager.h"
#include "Menu.h"
#include "Game.h"


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
    static void keyCallback(GLFWwindow *pWindow, int key, int scanncode, int action, int mods);

    int     m_iWidth;
    int     m_iHeight;

    float   m_fTime;


    GLFWwindow *m_pWindow;

    int m_iCurrState;
    enum States {game, menu};

    Game m_Game;
    Menu m_Menu;
};

#endif