#include "renderer.h"

batchRenderer createRenderer(int vertexCapacity)
{
    GLuint VBO, VAO, EBO, InstanceVBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &InstanceVBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //todo: burda bir hata var degerleri tekrar kontrol et
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCapacity * sizeof(Square), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Square), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Square), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);

    Shader ourShader = Shader("resources/shaders/vertexinstanced.vert", "resources/shaders/fragmentinstanced.frag");
    batchRenderer rend;

    rend.EBO = EBO;
    rend.VBO = VBO;
    rend.VAO = VAO;
    rend.InstanceVBO = InstanceVBO;
    rend.shader = ourShader;
    rend.vertices = (Square*)malloc(sizeof(Square) * vertexCapacity);
    rend.vertexCapacity = vertexCapacity;
    rend.vertexCount = 0;

    return rend;
}


void drawRenderer(batchRenderer* renderer)
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer->InstanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->vertexCount * sizeof(Square), renderer->vertices);

    glBindVertexArray(renderer->VAO);
    renderer->shader.use();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, renderer->vertexCount);

    glBindVertexArray(0);
    renderer->vertexCount = 0;
}

void killRenderer(batchRenderer* renderer)
{
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteBuffers(1, &renderer->EBO);

    renderer->shader.deleteProgram();
}

void growBuffer(batchRenderer* renderer)
{
    renderer->vertexCapacity *= 2; // Buffer kapasitesini iki katına çıkar
    renderer->vertices = (Square*)realloc(renderer->vertices, renderer->vertexCapacity * sizeof(Square));
    std::cout << "VBO buffer capacity increased to: " << renderer->vertexCapacity << " squares.\n";
}

void pushVertex(batchRenderer* renderer, float x, float y, float w, float h, vec4 color)
{
    if(renderer->vertexCount == renderer->vertexCapacity)
    {
        drawRenderer(renderer);
    }

    Square square;

    square.x = x;
    square.y = y;
    square.width = w;
    square.height = h;
    square.color = color;
    
    renderer->vertices[renderer->vertexCount++] = square;
}