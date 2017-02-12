#include "../include/Sprite.h"

void Sprite::create(const char *texturePath, float xStart, float yStart, float xLen, float yLen, float xTexLen, float yTexLen)
{
    // umrechnen
    float xSta = xStart / 400 -1;
    float ySta = 1 - yStart / 300;
    float xL   = (xStart + xLen) / 400 -1;
    float yL   = 1 - (yLen + yStart) / 300;

    //textur laden
    m_tex.loadTexture(texturePath, m_texID1);

    m_tex.getMesures(m_vTexDim.x, m_vTexDim.y);

    GLfloat vertices[] =
            {       //pos              //tex
                     xSta, ySta, 0.0f, 0.0f,            yTexLen / m_vTexDim.y,     //top left
                     xL,   ySta, 0.0f, xTexLen / m_vTexDim.x, yTexLen / m_vTexDim.y,     //top right
                     xSta, yL,   0.0f, 0.0f,            0.0f,                 //bottom left
                     xL,   yL,   0.0f, xTexLen / m_vTexDim.x, 0.0f                  //bottom right

            };

    /*
    std::cout << vertices[0] << ", " << vertices[1] << std::endl;
    std::cout << vertices[5] << ", " << vertices[6] << std::endl;
    std::cout << vertices[10] << ", " << vertices[11] << std::endl;
    std::cout << vertices[15] << ", " << vertices[16] << std::endl;
    */

    GLuint indices[] = {  // Note that we start from 0!
            0, 1, 2,   // First Triangle
            1, 2, 3    // Second Triangle
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    //alles innerhalb des vao, damit später nur vao callen
    glBindVertexArray(m_vao);

        //daten in vbo schreiben
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        //daten in element bo schreiebn
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //color attribut übergeben & aktivieren
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
        glEnableVertexAttribArray(0);

        //tex coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //shaderprogramm vor uniform !!
    m_shader.init("shader/spriteShader.vert", "shader/spriteShader.frag");

    //uniform gPos
    m_gPos = m_shader.getUniform("gPos");
    m_gTexShift = m_shader.getUniform("gTexShift");

    m_vPos.x = 0;
    m_vPos.y = 0;

    m_vTexShift.x = 0;
    m_vTexShift.y = 0;
}
void Sprite::del()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
}
void Sprite::render()
{
    m_shader.use();

    //alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //texture malen
    glBindTexture(GL_TEXTURE_2D, m_texID1);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_shader.unuse();
}
void Sprite::move(float x, float y)
{
    m_vPos.x += x;
    m_vPos.y += y;

    m_shader.use();
    glUniform3f(m_gPos, m_vPos.x, m_vPos.y, 0);
    m_shader.unuse();
}
void Sprite::shiftTexRect(float x, float y)
{
    m_vTexShift.x += x/m_vTexDim.x;
    m_vTexShift.y += y/m_vTexDim.y;

    m_shader.use();
    glUniform2f(m_gTexShift, m_vTexShift.x, m_vTexShift.y);
    m_shader.unuse();
}
void Sprite::setTexRect(float x, float y)
{
    m_vTexShift.x = x/m_vTexDim.x;
    m_vTexShift.y = y/m_vTexDim.y;

    m_shader.use();
    glUniform2f(m_gTexShift, m_vTexShift.x, m_vTexShift.y);
    m_shader.unuse();
}
