#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "../include/Framework.h"

int main()
{
    Framework f;
    f.init(800, 600, "Spaceshit");
    f.run();
    f.del();

    return 0;
}