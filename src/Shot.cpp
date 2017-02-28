#include "../include/Shot.h"

void Shot::init(float xPos, float yPos)
{
    m_sprite.create("data/Laser.png", xPos, yPos, 64, 64, 64, 64);

    m_bAlive = true;
}
void Shot::del()
{
    m_sprite.del();
}
void Shot::handleEvents()
{
    if(fLifetime >= 3.0f)
    {
        m_bAlive = false;
    }
}
void Shot::update(float fTime)
{
    m_sprite.move(0.0f, 0.8f * fTime);

    fLifetime += fTime;
}
void Shot::render()
{
    m_sprite.render();
}
Vector2f Shot::getPos()
{
    return m_sprite.getPos();
}