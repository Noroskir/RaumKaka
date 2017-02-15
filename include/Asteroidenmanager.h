#ifndef ASTEROIDENMANAGER_H
#define ASTEROIDENMANAGER_H

#include <list>
#include <iostream>

#include "Asteroid.h"

class Asteroidenmanager
{
public:
    Asteroidenmanager();
    ~Asteroidenmanager();

    void handleEvents();
    void update(float time);
    void render();



private:

    void spawnAst(float x, float y);

    std::list<Asteroid> m_AstList;

    bool m_bSpawn;
    float m_fSpawntime;

};



#endif