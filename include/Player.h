#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>

#include "Sprite.h"
#include "Shot.h"

class Player
{
public:

    void init();
    void del();
    void reset();

    void handleEvents();
    void update(float fTime);
    void render();

    void move(float x, float y);
    void shoot();

    std::list<Shot>* getShotList();

private:

    void animate(float fSpeed, int iRichtung);

    float m_fTime;
    Sprite m_sprite;

    std::list<Shot> m_ShotList;

    int   iAnimSteps;
    int   iCurrAnim;
    float fAnimCounter;

    Vector2f m_vPos;

    bool bMoving;

    bool bShotLock;
    float fShotTime;
};

#endif