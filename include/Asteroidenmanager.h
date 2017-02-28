#ifndef ASTEROIDENMANAGER_H
#define ASTEROIDENMANAGER_H

#include <list>
#include <iostream>

#include "Asteroid.h"
#include "Shot.h"

class Asteroidenmanager
{
public:
    Asteroidenmanager();
    ~Asteroidenmanager();

    void reset();

    void handleEvents();
    void update(float time);
    void render();

    void setShotList(std::list<Shot> *shotList);
private:

    void spawnAst(float x, float y);
    void checkCollison();

    std::list<Asteroid> m_AstList;
    std::list<Shot> *m_pShotList;

    bool m_bSpawn;
    float m_fSpawntime;

};



#endif