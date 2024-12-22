#ifndef GLEXTENSIONS_H
#define GLEXTENSIONS_H

#include "GL/glew.h"

//wrapper class for gl calls like draw triangles etc also
//todo: create first buffers and register, change size etc

enum ShapeType
{
    TRIANGLE = 0,
    POLYGON = 1,
    //circle
};

struct glextensions
{
    private:
        unsigned int VBO, VAO, EBO;

    public:
        void init();
        int drawShape(ShapeType/*, texture, */);
};

#endif