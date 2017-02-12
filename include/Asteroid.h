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

private:

    void animate(float speed);

    bool m_bAlive;
    Sprite m_sprite;

    int m_iAnimSteps;
    int m_iSpalten;
    int m_iZeilen;

    int m_iCurrSpalte;
    int m_iCurrZeile;
};



#endif