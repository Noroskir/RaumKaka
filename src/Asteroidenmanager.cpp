#include "../include/Asteroidenmanager.h"

Asteroidenmanager::Asteroidenmanager()
{
    m_fSpawntime = 3.0f;
    m_bSpawn = true;
}
Asteroidenmanager::~Asteroidenmanager()
{
    std::list<Asteroid>::iterator it;
    for(it = m_AstList.begin(); it != m_AstList.end();)
    {
        it->del();
        it = m_AstList.erase(it);
    }
}
void Asteroidenmanager::reset()
{
    m_fSpawntime = 3.0f;
    m_bSpawn = false;

    std::list<Asteroid>::iterator it;
    for(it = m_AstList.begin(); it != m_AstList.end();)
    {
        it->del();
        it = m_AstList.erase(it);
    }
}
void Asteroidenmanager::handleEvents()
{
    if(m_bSpawn)
    {
        int iPos = (rand() % 472) + 64;

        spawnAst(iPos, -100.0f);
        m_bSpawn = false;
    }
}
void Asteroidenmanager::update(float time)
{

    std::list<Asteroid>::iterator it;
    for(it = m_AstList.begin(); it != m_AstList.end();)
    {
        it->update(time);
        if(! it->m_bAlive)
        {
            it->del();
            it = m_AstList.erase(it);
        }
        else
        {
            it++;
        }
    }

    m_fSpawntime -= time;
    if(m_fSpawntime <= 0.0f)
    {
        m_fSpawntime += 3.0f;
        m_bSpawn = true;
    }

    checkCollison();
}
void Asteroidenmanager::render()
{
    std::list<Asteroid>::iterator it;
    for(it = m_AstList.begin(); it != m_AstList.end(); it++)
    {
        it->render();
    }
}
void Asteroidenmanager::spawnAst(float x, float y)
{
    Asteroid *a = new Asteroid();
    a->init(x, y);
    m_AstList.push_back(*a);

    delete  a;
}
void Asteroidenmanager::checkCollison()
{
    std::list<Asteroid>::iterator itAst = m_AstList.begin();
    std::list<Shot>::iterator itShot;
    while(itAst != m_AstList.end())
    {
        Vector2f vAstPos = itAst->getPos();
        for( itShot = m_pShotList->begin(); itShot != m_pShotList->end(); itShot++)
        {
            Vector2f vShotPos = itShot->getPos();

            if(vShotPos.x >= vAstPos.x - 64 && vShotPos.x <= vAstPos.x + 64
                    && vShotPos.y >= vAstPos.y && vShotPos.y <= vAstPos.y + 64)
            {
                itShot->m_bAlive = false;
                itAst->m_bAlive = false;
            }
        }
      itAst++;
    }

}
void Asteroidenmanager::setShotList(std::list<Shot> *shotList)
{
    m_pShotList = shotList;
}