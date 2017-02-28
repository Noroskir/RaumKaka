#ifndef MATH_H
#define MATH_H

struct Vector2i
{
    int x, y;
};
struct Vector2f
{
    float x, y;
};

struct Vector3f
{
    float x, y, z;
};
class Matrix3f
{
public:

    float m[3][3];
    Matrix3f()
    {
        for (unsigned int i = 0 ; i < 3 ; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                m[i][j] = 0.0f;
            }
        }
    }
    inline Matrix3f operator*(const Matrix3f& Right) const
    {
        Matrix3f Ret;
        for (unsigned int i = 0 ; i < 3 ; i++)
        {
            for (unsigned int j = 0 ; j < 3 ; j++)
            {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                              m[i][1] * Right.m[1][j] +
                              m[i][2] * Right.m[2][j];
            }
        }

        return Ret;
    }
};
inline Vector2f toGLCoord(const Vector2f windowCoords)
{
    Vector2f glCoords;
    glCoords.x = windowCoords.x / 400 - 1;
    glCoords.y = 1 - windowCoords.y / 300;
    return glCoords;
}
inline Vector2f toWindowCoord(const Vector2f glcoords)
{
    Vector2f winCoords;
    winCoords.x = glcoords.x * 400 + 400;
    winCoords.y = 300 - glcoords.y * 300;
    return winCoords;
}

#endif