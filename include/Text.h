#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include <stdlib.h>

#include "Shaderprogramm.h"
#include "Math.h"
#include "Texture.h"

class Text
{
public:
    Text();
    ~Text();

    void init();
    void createText(std::string text, Vector2f vpos, Vector3f vColor, float scale = 1.0f);
    void removeText(std::string text);

    void staticRender();                    //render created text, for buttons, etc
    void dynamicRender(std::string text, Vector2f vPos, Vector3f vColor, float scale = 1);   //render changing text

private:

    void readFont(const char *fontpath, const char *texturepath);

    Shaderprogramm m_shader;

    GLuint m_gTextColor;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    GLuint m_texID;

    Texture m_texture;

    Vector2i m_vTexSize;
    Vector3f m_vColor;

    struct Character
    {
        int iCharID;
        Vector2i vPos;
        Vector2i vSize;
        Vector2i vOffset;
        int iAdvance;
        int iPage;
    };
    struct RendChar
    {
        GLuint vao;
        GLuint vbo;
        GLuint ebo;

        int iStart;
    };
    std::map<char, Character> Characters;

    std::string m_sText;

    std::list<RendChar> m_lBuchstaben;
    std::list<std::pair<std::string, std::list<RendChar>::iterator>> m_lInfo;
};

#endif