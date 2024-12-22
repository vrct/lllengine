#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

struct Square{
    //float vertices[12];
    //indices;
    float x, y;
    float width, height;
    //float r, g, b, a;
    vec4 color;
};

//temporary
const float m_vertices[12] = {
    0.0f, 0.0f, 0.0f,  // bottom left
    0.0f, 1.0f, 0.0f,  // top left
    1.0f, 0.0f, 0.0f,  // bottom right
    1.0f, 1.0f, 0.0f   // top right
};

const int m_indices[] = {
    0, 1, 3,
    0, 3, 2
};

struct batchRenderer
{
    //vertex array object
    GLuint VAO;
    //vertex buffer object
    GLuint VBO;
    GLuint EBO;
    GLuint InstanceVBO;

    Shader shader;

    int vertexCapacity;
    int vertexCount;

    //float* vertices;
    Square* vertices;
    unsigned int* indices;
};

batchRenderer createRenderer(int vertexCapacity);
//temporary just for testing current policies
void drawRenderer(batchRenderer* renderer);
void killRenderer(batchRenderer* renderer);
void growBuffer(batchRenderer* renderer);

void pushVertex(batchRenderer* renderer,float x, float y, float w, float h, vec4 color);


#endif