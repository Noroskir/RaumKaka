#ifndef SHOT_H
#define SHOT_H


#include "Sprite.h"

class Shot
{
public:

    void init(float xPos, float yPos);
    void del();

    void handleEvents();
    void update(float fTime);
    void render();

    bool bAlive;

private:

    Sprite m_sprite;

    float fLifetime;
};


#endif