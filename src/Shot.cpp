#include "../include/Shot.h"

void Shot::init(float xPos, float yPos)
{
    m_sprite.create("data/Laser.png", xPos, yPos, 64, 64, 64, 64);

    bAlive = true;
}
void Shot::del()
{
    m_sprite.del();
}
void Shot::handleEvents()
{
    if(fLifetime >= 3.0f)
    {
        bAlive = false;
    }
}
void Shot::update(float fTime)
{
    m_sprite.move(0, 2 * fTime);

    fLifetime += fTime;
}
void Shot::render()
{
    m_sprite.render();
}