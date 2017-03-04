#include "../include/Text.h"

Text::Text()
{

}
Text::~Text()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);

    Characters.clear();
    m_lBuchstaben.clear();
}
void Text::init()
{
    readFont("data/Font/Font.fnt", "data/Font/Font_0.png");

    //shader
    m_shader.init("shader/textShader.vert", "shader/textShader.frag");
    m_gTextColor = m_shader.getUniform("gColor");
}
void Text::createText(std::string text, Vector2f vpos,  Vector3f vColor, float scale)
{
    std::list<RendChar>::iterator itC = m_lBuchstaben.end();
    m_lInfo.push_back(std::make_pair(text, itC));

    m_vColor = vColor;

    float xpos = toGLCoord(vpos).x;
    float ypos = toGLCoord(vpos).y;

    m_sText = text;
    int size = m_sText.length();

    for(int i = 0; i < size; i++)
    {
        Character ch = Characters[m_sText[i]];
        RendChar rch;

        float texPosx = static_cast<float>(ch.vPos.x) / static_cast<float>(m_vTexSize.x);
        float texPosy = static_cast<float>(ch.vPos.y) / static_cast<float>(m_vTexSize.y);

        float xoffset = static_cast<float>(ch.vOffset.x) / static_cast<float>(m_vTexSize.x);
        float yoffset = static_cast<float>(ch.vOffset.y) / static_cast<float>(m_vTexSize.y);

        float xsize = static_cast<float>(ch.vSize.x) / static_cast<float>(m_vTexSize.x);
        float ysize = static_cast<float>(ch.vSize.y) / static_cast<float>(m_vTexSize.y);

        GLfloat vertices[] = {
                //position                                                          //texCoords
                xpos + xoffset * scale,           ypos - yoffset * scale,           texPosx,         texPosy,         //top left
                xpos + (xoffset + xsize) * scale, ypos - yoffset * scale,           texPosx + xsize, texPosy,         //top right
                xpos + xoffset * scale,           ypos - (yoffset + ysize) * scale, texPosx,         texPosy + ysize, //bottom left
                xpos + (xoffset + xsize) * scale, ypos - (yoffset + ysize) * scale, texPosx + xsize, texPosy + ysize  //bottom right
        };


        GLuint indices[] = {
                0, 1, 2, //erstes dreieck
                1, 2, 3 //zweites dreiek
        };

        glGenVertexArrays(1, &rch.vao);
        glGenBuffers(1, &rch.vbo);
        glGenBuffers(1, &rch.ebo);

        glBindVertexArray(rch.vao);

            glBindBuffer(GL_ARRAY_BUFFER, rch.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rch.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

            //position & textCoordinaten
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) 0);
            glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        m_lBuchstaben.push_back(rch);

        xpos = xpos + (static_cast<float>(ch.iAdvance) / static_cast<float>(m_vTexSize.x)) * scale;
    }

    m_shader.use();
    glUniform3f(m_gTextColor, m_vColor.x, m_vColor.y, m_vColor.z);
    m_shader.unuse();
}
void Text::staticRender()
{
    m_shader.use();

    glBindTexture(GL_TEXTURE_2D, m_texID);

    std::list<RendChar>::iterator itB;
    for(itB = m_lBuchstaben.begin(); itB != m_lBuchstaben.end(); itB++)
    {
        glBindVertexArray(itB->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    m_shader.unuse();
}
void Text::dynamicRender(std::string text, Vector2f vPos, Vector3f vColor, float scale)
{
    //std::list<RendChar> lBuchst;

    float xpos = toGLCoord(vPos).x;
    float ypos = toGLCoord(vPos).y;

    m_sText = text;
    int size = m_sText.length();

    m_shader.use();
    glUniform3f(m_gTextColor, vColor.x, vColor.y, vColor.z);

    for(int i = 0; i < size; i++)
    {
        Character ch = Characters[m_sText[i]];
        RendChar rch;

        float texPosx = static_cast<float>(ch.vPos.x) / static_cast<float>(m_vTexSize.x);
        float texPosy = static_cast<float>(ch.vPos.y) / static_cast<float>(m_vTexSize.y);

        float xoffset = static_cast<float>(ch.vOffset.x) / static_cast<float>(m_vTexSize.x);
        float yoffset = static_cast<float>(ch.vOffset.y) / static_cast<float>(m_vTexSize.y);

        float xsize = static_cast<float>(ch.vSize.x) / static_cast<float>(m_vTexSize.x);
        float ysize = static_cast<float>(ch.vSize.y) / static_cast<float>(m_vTexSize.y);

        GLfloat vertices[] = {
                //position                                        //texCoords
                xpos + xoffset * scale,           ypos - yoffset * scale,         texPosx,         texPosy,         //top left
                xpos + (xoffset + xsize) * scale, ypos - yoffset * scale,         texPosx + xsize, texPosy,         //top right
                xpos + xoffset * scale,           ypos - (yoffset + ysize) * scale, texPosx,         texPosy + ysize, //bottom left
                xpos + (xoffset + xsize) * scale, ypos - (yoffset + ysize) * scale, texPosx + xsize, texPosy + ysize  //bottom right
        };


        GLuint indices[] = {
                0, 1, 2, //erstes dreieck
                1, 2, 3 //zweites dreiek
        };

        glGenVertexArrays(1, &rch.vao);
        glGenBuffers(1, &rch.vbo);
        glGenBuffers(1, &rch.ebo);

        glBindVertexArray(rch.vao);

            glBindBuffer(GL_ARRAY_BUFFER, rch.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rch.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

            //position & textCoordinaten
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) 0);
            glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        //lBuchst.push_back(rch);


        glBindTexture(GL_TEXTURE_2D, m_texID);
        glBindVertexArray(rch.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        xpos = xpos + (static_cast<float>(ch.iAdvance) / static_cast<float>(m_vTexSize.x)) * scale;
    }
    m_shader.unuse();
}
void Text::readFont(const char *fontpath, const char *texturepath)
{
    //textur laden
    m_texture.loadTexture(texturepath, m_texID);
    m_texture.getMesures(m_vTexSize.x,  m_vTexSize.y);

    //Buchstabendaten einlesen
    std::list<std::string> output;

    std::ifstream file;
    file.open(fontpath);

    if(file.is_open())
    {
        while(!file.eof())
        {
            std::string zeile;
            getline(file, zeile);

            std::string wort1;
            for(int i = 0; i < 5; i++)
            {
                wort1 += zeile[i];
            }
            if(wort1 == "char ") output.push_back(zeile);
        }
    }
    else
    {
        std::cout << "ERROR::Konnte Font-Datei nicht öffnen!" << std::endl;
    }


    std::list<std::string>::iterator it;
    for(it = output.begin(); it != output.end(); it++)
    {
        std::vector<std::string> worte;

        std::istringstream zeile(*it);
        while(zeile)
        {
            std::string wort;
            zeile >> wort;
            worte.push_back(wort);
        }

        worte[1].erase(0, 3);
        char c = std::stoi(worte[1]);

        Character ch;
        ch.iCharID = std::stoi(worte[1]);

        worte[2].erase(0, 2);
        worte[3].erase(0, 2);
        ch.vPos.x = std::stoi(worte[2]);
        ch.vPos.y = std::stoi(worte[3]);

        worte[4].erase(0,6);
        worte[5].erase(0,7);
        ch.vSize.x = std::stoi(worte[4]);
        ch.vSize.y = std::stoi(worte[5]);

        worte[6].erase(0, 8);
        worte[7].erase(0, 8);
        ch.vOffset.x = std::stoi(worte[6]);
        ch.vOffset.y = std::stoi(worte[7]);

        worte[8].erase(0, 9);
        ch.iAdvance = std::stoi(worte[8]);
        //alles andere einlesen !

        Characters.insert(std::make_pair(c, ch));
    }
}
void Text::removeText(std::string text)
{
    std::list<std::pair<std::string, std::list<RendChar>::iterator>>::iterator it = m_lInfo.begin();
    while(it != m_lInfo.end())
    {
        if(it->first == text)
        {
            std::list<RendChar>::iterator itRC = it->second;
            for(int i = 0; i < text.length(); i++)
            {
                //m_lBuchstaben.erase(itRC);
                itRC++;
            }
            break;
        } else
        {
            it++;
        }
    }
}