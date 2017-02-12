#include "../include/Asteroid.h"

void Asteroid::init(float x, float y)
{
    m_sprite.create("data/Asteroid.png", x, y, 64, 64, 64, 64);
    m_bAlive = true;

    m_iAnimSteps = 20;
    m_iSpalten = 10;
    m_iZeilen = 2;

}
void Asteroid::del()
{
    m_sprite.del();
}
void Asteroid::update(float time)
{
    m_sprite.move(0, -50 * time);
}
void Asteroid::render()
{
    m_sprite.render();
}
void Asteroid::animate(float speed)
{

}