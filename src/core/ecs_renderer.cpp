#include "ecs_renderer.h"

#include <renderer.h>

Renderer::Renderer(Shader& s) : shader(s), vertexCount(0)
{
    initBuffers();
};

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    shader.deleteProgram();
}

void Renderer::initBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    const unsigned int indices[] = {
        0, 1, 3, // İlk üçgen
        0, 3, 2  // İkinci üçgen
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxVertices * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Renderer::pushVertex(const Vertex& vertex)
{
    if(vertexCount >= maxVertices)
    {
        draw();
    }

    /*matrix4 transform = matrix4().identity();
    transform.translateMatrix(vec4(vertex.x, vertex.y, 0));
    transform.scaleMatrix(vec4(vertex.w, vertex.h, 1.0f));

    shader.setMatrix4("transform", transform);*/
    //vertices.push_back(vertex);

    // Sol alt köşe
    vertices.push_back(Vertex{vertex.x, vertex.y, vertex.w, vertex.h, vertex.color});
    // Sol üst köşe
    vertices.push_back(Vertex{vertex.x, vertex.y + vertex.h, vertex.w, vertex.h, vertex.color});
    // Sağ alt köşe
    vertices.push_back(Vertex{vertex.x + vertex.w, vertex.y, vertex.w, vertex.h, vertex.color});
    // Sağ üst köşe
    vertices.push_back(Vertex{vertex.x + vertex.w, vertex.y + vertex.h, vertex.w, vertex.h, vertex.color});

    unsigned int indices_offset = vertexCount * 4;

    indices.push_back(indices_offset);
    indices.push_back(indices_offset + 1);
    indices.push_back(indices_offset + 2);
    indices.push_back(indices_offset + 1);
    indices.push_back(indices_offset + 2);
    indices.push_back(indices_offset + 3);

    vertexCount++;

    //std::cout << "VERTICES COUNT: " << vertices[vertexCount - 1].x << " " << vertices[vertexCount - 1].y << " " << vertices[vertexCount - 1].w << " " << vertices[vertexCount - 1].h << std::endl;
    //std::cout << "TRANSFORM: " << transform << std::endl;
}

void Renderer::updateBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error in updateBuffer: " << error << std::endl;
    }
}

void Renderer::updateEntitiesVertices(Entity &entity, unsigned int verticeOffset) {
    auto* position = entity.getComponent<PositionComp>(Position);
    auto* size = entity.getComponent<SizeComp>(Size);
    auto* color = entity.getComponent<ColorComp>(Color);

    //todo: add texture check auch
    if (!position || !size || !color) return;

    vertices[verticeOffset] = Vertex{position->x, position->y, size->w, size->h, color->color, 0,0};
    vertices[verticeOffset + 1] = Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0};
    vertices[verticeOffset + 2] = Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1};
    vertices[verticeOffset + 3] = Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1};

    unsigned int byteOffset = verticeOffset * sizeof(Vertex);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, byteOffset, 4 * sizeof(Vertex), &vertices[verticeOffset]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Renderer::addEntities(Entity& entity) {
    auto* position = entity.getComponent<PositionComp>(Position);
    auto* size = entity.getComponent<SizeComp>(Size);
    auto* color = entity.getComponent<ColorComp>(Color);
    auto* texture = entity.getComponent<TextureComp>(Texture);

    if (!position || !size || !color) return;

    unsigned int vertexStartIndex  = vertices.size();

    if (texture) {
        shader.setBool("hasTexture", GL_TRUE);
        texture->texture.bind();
    } else {
        shader.setBool("hasTexture", GL_FALSE);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    vertices.push_back(Vertex{position->x, position->y, size->w, size->h, color->color, 0,0});
    // Sol üst köşe
    vertices.push_back(Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0});
    // Sağ alt köşe
    vertices.push_back(Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1});
    // Sağ üst köşe
    vertices.push_back(Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1});

    //unsigned int indices_offset = vertexCount * 4;
    //todo: check calculation here
    unsigned int indices_offset = vertexStartIndex;

    indices.push_back(indices_offset);
    indices.push_back(indices_offset + 1);
    indices.push_back(indices_offset + 2);
    indices.push_back(indices_offset + 1);
    indices.push_back(indices_offset + 2);
    indices.push_back(indices_offset + 3);

    entity.setVertexOffset(vertexStartIndex);
    entity.setIndicesOffset(indices.size() - 6);

    vertexCount += 4;
}


void Renderer::drawEntities(std::vector<Entity>& entities) {

    if (vertexCount == 0) {
        std::cerr << "No vertex buffer created" << std::endl;
        vertices.clear();
        indices.clear();

        for (auto& entity : entities) {addEntities(entity);}

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        //glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

        return;
    }

    int counter = 0;
    for (auto& entity : entities) {
        if (entity.isDirty()) {
            counter++;
            //std::cout << "ENTITY IS DIRTY UPDATED " << counter << std::endl;
            updateEntitiesVertices(entity, entity.getVertexOffset());
            entity.updateCachedVersion();
        }
    }

    // std::vector<Vertex> updatedVertices;
    // std::vector<unsigned int> updatedIndices;
    // unsigned int localVertexCount = 0;

    //vertices.clear();

    shader.use();
    shader.setVec4("windowSize", windowSize);

    // for (const auto& entity : entities) {
    //     if (!entity.isDirty()) continue;
    //     auto* position = entity.getComponent<PositionComp>(Position);
    //     auto* size = entity.getComponent<SizeComp>(Size);
    //     auto* color = entity.getComponent<ColorComp>(Color);
    //     auto* texture = entity.getComponent<TextureComp>(Texture);
    //
    //     //if (position && size && color) {
    //         if (texture) {
    //             shader.setBool("hasTexture", GL_TRUE);
    //             texture->texture.bind();
    //         } else {
    //             shader.setBool("hasTexture", GL_FALSE);
    //             glBindTexture(GL_TEXTURE_2D, 0);
    //         }
    //         updatedVertices.push_back(Vertex{position->x, position->y, size->w, size->h, color->color, 0,0});
    //         // Sol üst köşe
    //         updatedVertices.push_back(Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0});
    //         // Sağ alt köşe
    //         updatedVertices.push_back(Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1});
    //         // Sağ üst köşe
    //         updatedVertices.push_back(Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1});
    //
    //         unsigned int indices_offset = localVertexCount * 4;
    //
    //         updatedIndices.push_back(indices_offset);
    //         updatedIndices.push_back(indices_offset + 1);
    //         updatedIndices.push_back(indices_offset + 2);
    //         updatedIndices.push_back(indices_offset + 1);
    //         updatedIndices.push_back(indices_offset + 2);
    //         updatedIndices.push_back(indices_offset + 3);
    //
    //         //std::cout << "X: " << position->x << "Y: " << position->y << std::endl;
    //
    //         localVertexCount++;
    //         entity.updateCachedVersion();
    //     //}
    // }

    //draw();
    // if(localVertexCount == 0) return;
    //
    // //updateBuffers();
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, updatedVertices.size() * sizeof(Vertex), updatedVertices.data());
    //
    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    // glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, updatedIndices.size() * sizeof(unsigned int), updatedIndices.data());

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error in updateBuffer: " << error << std::endl;
    }

    //shader.setVec4("windowSize", vec4(640,360));

    glBindVertexArray(VAO);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    //todo: nachdem unterschied wechsel hier
    //clear();
}

void Renderer::draw()
{
    if(vertexCount == 0) return;


    updateBuffers();

    //shader.setVec4("windowSize", vec4(640,360));
    
    glBindVertexArray(VAO);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    clear();
}

void Renderer::clear()
{
    vertices.clear();
    indices.clear();
    vertexCount = 0;
}
