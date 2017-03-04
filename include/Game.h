#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <string>

#include "Text.h"
#include "Sprite.h"
#include "Player.h"
#include "Asteroidenmanager.h"


class Game
{
public:

    void init(GLFWwindow *pWindow);
    void reset();
    void exit();
    void leaveState();
    void enterState();

    void handleEvents();
    void update(float fTime);
    void render();

private:

    float m_fTime;

    GLFWwindow *m_pWindow;
    Text m_Text;
    Sprite m_sBackground;
    Player m_Player;
    Asteroidenmanager m_AstManager;

};



#endif