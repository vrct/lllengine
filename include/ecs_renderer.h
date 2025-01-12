#ifndef ECS_RENDERER_H
#define ECS_RENDERER_H

#include "vector"
#include "vec4.h"
#include "shader.h"
#include "ecs/entity.h"
#include "ecs/components/positioncomp.h"
#include "ecs/components/sizecomp.h"
#include "ecs/components/colorcomp.h"
#include "ecs/components/texturecomp.h"

struct Vertex {
    float x,y;
    float w,h;
    vec4 color;
    float u, v;
};

class Renderer {
    public:
        Renderer(Shader& shader);
        ~Renderer();

        //todo: remove from field make setter ?
        vec4 windowSize;
        void pushVertex(const Vertex& vertex);
        void draw();
        void drawEntities(std::vector<Entity>& entities);
        void clear();

    private:
        unsigned int VAO, VBO, EBO;
        Shader& shader;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int vertexCount = 0;
        const unsigned int maxVertices = 1000000;

        void initBuffers();
        void updateBuffers();
        void addEntities(Entity& entity);
        void updateEntitiesVertices(Entity& entity, unsigned int verticeOffset);
};



#endif