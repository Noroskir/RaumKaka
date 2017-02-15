#include "../include/Asteroid.h"

void Asteroid::init(float x, float y)
{
    m_sprite.create("data/Asteroid.png", x, y, 64, 64, 64, 64);
    m_bAlive = true;

    m_iAnimSteps = 20;
    m_iSpalten = 10;

    m_iCurrAnim = 0;
    m_iCurrSpalte = 0;

    m_fAnimCount = 0.0f;

    m_fLifetime = 40.0f;
}
void Asteroid::del()
{
    m_sprite.del();
}
void Asteroid::update(float time)
{
    m_fLifetime -= time;

    if(m_fLifetime < 0.0f)
    {
        m_bAlive = false;
    }
    m_sprite.move(0, -.1 * time);
    animate(time * 8);
}
void Asteroid::render()
{
    m_sprite.render();
}
void Asteroid::animate(float speed)
{
    m_fAnimCount += speed;
    if(m_fAnimCount >= 1)
    {
        m_fAnimCount -= 1;
        m_iCurrAnim = (m_iCurrAnim + 1) % m_iAnimSteps;
        m_iCurrSpalte = m_iCurrAnim % m_iSpalten;
        if(m_iCurrAnim < 10 )
        {
            m_sprite.setTexRect(m_iCurrSpalte * 64, 64);
        }
        else
        {
            m_sprite.setTexRect(m_iCurrSpalte * 64, 0);
        }


    }
}