#include "../include/Player.h"

void Player::init(float *time)
{

    m_vPos.x = 380;
    m_vPos.y = 500;

    m_sprite.create("data/Player.png", m_vPos.x, m_vPos.y, 64, 64, 64, 64);
    m_sprite.shiftTexRect(64 * 5, 0);
    m_fTime = time;

    //animations phase setzten
    iCurrAnim = 6;
    fAnimCounter = 0;
    iAnimSteps = 11;

    bMoving = false;
    bShotLock = false;

    fShotTime = 0.0f;
}
void Player::del()
{
    m_sprite.del();
}
void Player::handleEvents()
{

}
void Player::update(float fTime)
{
    if(!bMoving)
    {
        if (iCurrAnim < 5)
        {
            animate(13 * *m_fTime, 1);
        } else if (iCurrAnim > 5)
        {
            animate(13 * *m_fTime, -1);
        }
    }
    bMoving = false;

    fShotTime += fTime;
    if(fShotTime >= 1.0f)
    {
        fShotTime -= 1.0f;
        bShotLock = false;
    }
}
void Player::render()
{
    m_sprite.render();

    std::list<Shot>::iterator it = m_ShotList.begin();
    while(it != m_ShotList.end())
    {
        if(it->bAlive == true)
        {

            it->handleEvents();
            it->update(*m_fTime);
            it->render();

            it++;
        }
        else
        {
            it->del();
            it = m_ShotList.erase(it);
        }


    }
}
void Player::move(float x, float y)
{
    bMoving = true;

    m_vPos.x += x * 400;
    m_vPos.y += y * 300;

    m_sprite.move(x, y);
    if(x < 0) animate(20 * *m_fTime, -1);
    if(x > 0) animate(20 * *m_fTime,  1);
}
void Player::animate(float fSpeed, int iRichtung)
{
    fAnimCounter += fSpeed;

    if( fAnimCounter >= 1)
    {
        fAnimCounter -= 1;
        iCurrAnim += iRichtung * 1;
        if(iCurrAnim <= iAnimSteps && iCurrAnim > 0)
        {
            m_sprite.shiftTexRect(64 * iRichtung, 0);
        }
        else if(iCurrAnim <= 0)
        {
            iCurrAnim++;
        }
        else
        {
            iCurrAnim--;
        }
    }
}
void Player::shoot()
{

    if(!bShotLock)
    {
        Shot s;
        s.init(m_vPos.x, m_vPos.y);

        m_ShotList.push_back(s);
        bShotLock = true;
    }
}