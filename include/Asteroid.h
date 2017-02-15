#ifndef ASTEROID_H
#define ASTEROID_H


#include "Sprite.h"


class Asteroid
{
public:

    void init(float x, float y);
    void del();

    void update(float time);
    void render();

    bool m_bAlive;

private:

    void animate(float speed);
    Sprite m_sprite;


    float m_fAnimCount;

    int m_iAnimSteps;
    int m_iSpalten;

    int m_iCurrAnim;
    int m_iCurrSpalte;

    float m_fLifetime;
};



#endif