#ifndef ECS_RENDERER_H
#define ECS_RENDERER_H

#include <ecs/entityManager.h>

#include "vector"
#include "vec4.h"
#include "shader.h"
#include "ecs/entity.h"

#include "stb_truetype.h"
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
        Renderer(Shader& shader, ComponentManager& componentManager);
        ~Renderer();

        //todo: remove from field make setter ?
        vec4 windowSize;
        ComponentManager& componentManager;
        void pushVertex(const Vertex& vertex);
        void draw();
        void drawEntities(std::vector<Entity>& entities,const float deltaTime);
        void addEntitiesBuffer();
        void drawEntitiesBuffer();
        void clear();

        void loadTextAtlas(const std::string& fontPath, unsigned int fontSize);
        void drawText(const std::string& text, float x, float y, float scale, const vec4& color);

    private:
        unsigned int VAO, VBO, EBO;
        unsigned int textAtlasTextureID;
        Shader& shader;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int vertexCount = 0;
        const unsigned int maxVertices = 1000000;

        void initBuffers();
        void updateBuffers();
        void addEntities(Entity& entity);

        void updateEntitiesVerticesBuffer();

        void removeEntities(Entity& entity);
        void updateEntitiesVertices(Entity& entity, unsigned int verticeOffset);
        std::vector<Vertex> updateEntitiesVerticesV(Entity& entity, unsigned int verticeOffset);

        unsigned char* fontData;
        stbtt_bakedchar cdata[96];  // ASCII karakterler için veri
};



#endif