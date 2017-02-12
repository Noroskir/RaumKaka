#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "Shaderprogramm.h"
#include "Texture.h"
#include "Math.h"

class Sprite
{
public:

    void create(const char *texturePath, float xStart, float yStart,
                float xLen, float yLen, float xTexLen, float yTexLen);
    void del();

    void render();
    void move(float x, float y);

    void shiftTexRect(float x, float y);
    void setTexRect(float x, float y);

private:


    GLuint m_vao;
    GLuint m_ebo;
    GLuint m_vbo;

    GLuint m_texID1;

    GLuint m_gPos;
    GLuint m_gTexShift;

    Shaderprogramm m_shader;
    Texture m_tex;

    Vector2f m_vPos;
    Vector2f m_vTexShift;
    Vector2i m_vTexDim;

};


#endif