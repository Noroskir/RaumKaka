#include "../include/Asteroidenmanager.h"

Asteroidenmanager::Asteroidenmanager()
{
    m_fSpawntime = 3.0f;
    m_bSpawn = false;
    //spawnAst(300, 400);
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
void Asteroidenmanager::handleEvents()
{
    if(m_bSpawn == true)
    {
        spawnAst(300.0f, -100.0f);
        m_bSpawn = false;
    }
}
void Asteroidenmanager::update(float time)
{
    std::list<Asteroid>::iterator it;
    for(it = m_AstList.begin(); it != m_AstList.end();)
    {
        it->update(time);
        if(it->m_bAlive == false)
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