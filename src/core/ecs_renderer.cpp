#include "ecs_renderer.h"
#include <renderer.h>
#include <ecs/entityManager.h>
#include <string>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

Renderer::Renderer(Shader& s, ComponentManager& e) : shader(s), componentManager(e)
{
    initBuffers();
};

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    if (textAtlasTextureID != 0) {
        glDeleteTextures(1, &textAtlasTextureID);
    }

    shader.deleteProgram();
}

void Renderer::initBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * 2 * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxVertices * 2 * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
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
    // auto* position = entity.getComponent<PositionComp>(Position);
    // auto* size = entity.getComponent<SizeComp>(Size);
    // auto* color = entity.getComponent<ColorComp>(Color);
    //
    // //todo: add texture check auch
    // //if (!position || !size || !color) return;
    //
    // vertices[verticeOffset] = Vertex{position->x, position->y, size->w, size->h, color->color, 0,0};
    // vertices[verticeOffset + 1] = Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0};
    // vertices[verticeOffset + 2] = Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1};
    // vertices[verticeOffset + 3] = Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1};
    //
    // unsigned int byteOffset = verticeOffset * sizeof(Vertex);
    //todo: open here after testing
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, byteOffset, 4 * sizeof(Vertex), &vertices[verticeOffset]);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::vector<Vertex> Renderer::updateEntitiesVerticesV(Entity &entity, unsigned int verticeOffset) {
    // auto* position = entity.getComponent<PositionComp>(Position);
    // auto* size = entity.getComponent<SizeComp>(Size);
    // auto* color = entity.getComponent<ColorComp>(Color);
    //
    // //todo: add texture check auch
    // //if (!position || !size || !color) return;
    //
    // vertices[verticeOffset] = Vertex{position->x, position->y, size->w, size->h, color->color, 0,0};
    // vertices[verticeOffset + 1] = Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0};
    // vertices[verticeOffset + 2] = Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1};
    // vertices[verticeOffset + 3] = Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1};
    //
    // return std::vector<Vertex>{vertices[verticeOffset], vertices[verticeOffset + 1], vertices[verticeOffset + 2], vertices[verticeOffset + 3]};
    return {};
}


void Renderer::removeEntities(Entity &entity) {
    //todo: remove entity method add
}



void Renderer::addEntities(Entity& entity) {
    // auto* position = entity.getComponent<PositionComp>(Position);
    // auto* size = entity.getComponent<SizeComp>(Size);
    // auto* color = entity.getComponent<ColorComp>(Color);
    // auto* texture = entity.getComponent<TextureComp>(Texture);
    //
    // if (!position || !size || !color) return;
    //
    // unsigned int vertexStartIndex  = vertices.size();
    //
    // if (!texture) {
    //     shader.setBool("hasTexture", GL_FALSE);
    //     glBindTexture(GL_TEXTURE_2D, 0);
    // } else {
    //     shader.setBool("hasTexture", GL_TRUE);
    //     texture->texture.bind();
    // }
    //
    // vertices.push_back(Vertex{position->x, position->y, size->w, size->h, color->color, 0,0});
    // // Sol üst köşe
    // vertices.push_back(Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0});
    // // Sağ alt köşe
    // vertices.push_back(Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1});
    // // Sağ üst köşe
    // vertices.push_back(Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1});
    //
    // //unsigned int indices_offset = vertexCount * 4;
    // //todo: check calculation here
    // //unsigned int indices_offset = vertexStartIndex;
    // unsigned int indices_offset = vertexCount;
    //
    // indices.push_back(indices_offset);
    // indices.push_back(indices_offset + 1);
    // indices.push_back(indices_offset + 2);
    // indices.push_back(indices_offset + 1);
    // indices.push_back(indices_offset + 2);
    // indices.push_back(indices_offset + 3);
    //
    // entity.setVertexOffset(vertexStartIndex);
    // entity.setIndicesOffset(indices.size() - 6);
    //
    // vertexCount += 4;
}

void Renderer::updateEntitiesVerticesBuffer() {
    for (Entity entityId = 0; entityId < componentManager.getEntityMasks().size(); entityId++) {
        auto& mask = componentManager.getEntityMasks()[entityId];
        if (mask.test(Position) && mask.test(Size) && mask.test(Color) || mask.test(Texture)) {
            PositionComponent* position = componentManager.getPositionComponent(entityId);
            SizeComponent* size = componentManager.getSizeComponent(entityId);
            ColorComponent* color = componentManager.getColorComponent(entityId);
            TextureComponent* texture = componentManager.getTextureComponent(entityId);

            texture->texture.bind();

            auto x = position->x;
            auto y = position->y;
            auto w = size->w;
            auto h = size->h;
            auto color2 = color->color;

            unsigned int verticeOffset = componentManager.entityVerticeOffsets[entityId];
            vertices[verticeOffset] =     Vertex{x, y, w, h, color2, 0,0};
            vertices[verticeOffset + 1] = Vertex{x, y + h, w, h, color2, 1,0};
            vertices[verticeOffset + 2] = Vertex{x + w, y, w, h, color2, 0,1};
            vertices[verticeOffset + 3] = Vertex{x + w, y + h, w, h, color2, 1, 1};
        }
    }

    // for (unsigned int i = 0; i < entity_manager.entities.size(); i++) {
    //     auto entityId = entity_manager.entities[i];
    //     PositionComponent position = entity_manager.componentManager.positionComponents[i];
    //     SizeComponent size = entity_manager.componentManager.sizeComponents[i];
    //     ColorComponent color = entity_manager.componentManager.colorComponents[i];
    //
    //     auto x = position.x;
    //     auto y = position.y;
    //     auto w = size.w;
    //     auto h = size.h;
    //     auto color2 = color.color;
    //
    //     unsigned int verticeOffset = (entityId - 1) * 4;
    //     vertices[verticeOffset] =     Vertex{x, y, w, h, color2, 0,0};
    //     vertices[verticeOffset + 1] = Vertex{x, y + h, w, h, color2, 1,0};
    //     vertices[verticeOffset + 2] = Vertex{x + w, y, w, h, color2, 0,1};
    //     vertices[verticeOffset + 3] = Vertex{x + w, y + h, w, h, color2, 1, 1};
    // }
    // int count = 100;
    // if (count-- == 0) {return;}
    // auto* color = entity_manager.getComponent<ColorComponent>(entityId, Color);
    // auto* position = entity_manager.getComponent<PositionComponent>(entityId, (int)Position);
    // auto* size = entity_manager.getComponent<SizeComponent>(entityId, Size);
    // //
    // // PositionComponent positiona {1,1};
    // // SizeComponent sizea {40,40};
    // // ColorComponent colora {vec4{1,1,1,1}};
    // // auto* position = &positiona;
    // // auto* size = &sizea;
    // // auto* color = &colora;
    //
    // float x = position->x;
    // float y = position->y;
    // float w = size->w;
    // float h = size->h;
    // vec4 color2 = color->color;

    //todo: add texture check auch
    //if (!position || !size || !color) return;
    // unsigned int verticeOffset = (entityId - 1) * 4;
    // vertices[verticeOffset] =     Vertex{x, y, w, h, color2, 0,0};
    // vertices[verticeOffset + 1] = Vertex{x, y + h, w, h, color2, 1,0};
    // vertices[verticeOffset + 2] = Vertex{x + w, y, w, h, color2, 0,1};
    // vertices[verticeOffset + 3] = Vertex{x + w, y + h, w, h, color2, 1, 1};
}

void Renderer::addEntitiesBuffer() {
    for (Entity entityId = 0; entityId < componentManager.getEntityMasks().size(); entityId++) {
        auto& mask = componentManager.getEntityMasks()[entityId];
        if (mask.test(Position) && mask.test(Size) && mask.test(Color) || mask.test(Texture)) {
            PositionComponent* position = componentManager.getPositionComponent(entityId);
            SizeComponent* size = componentManager.getSizeComponent(entityId);
            ColorComponent* color = componentManager.getColorComponent(entityId);
            TextureComponent* texture = componentManager.getTextureComponent(entityId);

            texture->texture.bind();

            vertices.push_back(Vertex{position->x, position->y, size->w, size->h, color->color, 0,0});
            // Sol üst köşe
            vertices.push_back(Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0});
            // Sağ alt köşe
            vertices.push_back(Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1});
            // Sağ üst köşe
            vertices.push_back(Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1});

            //unsigned int indices_offset = vertexCount * 4;
            //todo: check calculation here
            //unsigned int indices_offset = vertexStartIndex;
            unsigned int indices_offset = vertexCount;

            indices.push_back(indices_offset);
            indices.push_back(indices_offset + 1);
            indices.push_back(indices_offset + 2);
            indices.push_back(indices_offset + 1);
            indices.push_back(indices_offset + 2);
            indices.push_back(indices_offset + 3);

            // entity.setVertexOffset(vertexStartIndex);
            // entity.setIndicesOffset(indices.size() - 6);

            vertexCount += 4;
        }
        else {
            // std::cerr << "Entity doesn't exist ID: " <<  entityId << std::endl;
        }
    }

    // for (unsigned int i = 0; i < entity_manager.entities.size(); i++) {
    //     auto entityId = entity_manager.entities[i];
    //     PositionComponent position = entity_manager.componentManager.positionComponents[i];
    //     SizeComponent size = entity_manager.componentManager.sizeComponents[i];
    //     ColorComponent color = entity_manager.componentManager.colorComponents[i];
    //
    //     // std::cout << entityId << "POS: " << position.x << " " << position.y << std::endl;
    //
    //     vertices.push_back(Vertex{position.x, position.y, size.w, size.h, color.color, 0,0});
    //     // Sol üst köşe
    //     vertices.push_back(Vertex{position.x, position.y + size.h, size.w, size.h, color.color, 1,0});
    //     // Sağ alt köşe
    //     vertices.push_back(Vertex{position.x + size.w, position.y, size.w, size.h, color.color, 0,1});
    //     // Sağ üst köşe
    //     vertices.push_back(Vertex{position.x + size.w, position.y + size.h, size.w, size.h, color.color, 1, 1});
    //
    //     //unsigned int indices_offset = vertexCount * 4;
    //     //todo: check calculation here
    //     //unsigned int indices_offset = vertexStartIndex;
    //     unsigned int indices_offset = vertexCount;
    //
    //     indices.push_back(indices_offset);
    //     indices.push_back(indices_offset + 1);
    //     indices.push_back(indices_offset + 2);
    //     indices.push_back(indices_offset + 1);
    //     indices.push_back(indices_offset + 2);
    //     indices.push_back(indices_offset + 3);
    //
    //     // entity.setVertexOffset(vertexStartIndex);
    //     // entity.setIndicesOffset(indices.size() - 6);
    //
    //     vertexCount += 4;
    // }

    // for (auto entityId : entity_manager.entities) {
    //     auto* position = entity_manager.getComponent<PositionComponent>(entityId, (int)Position);
    //     auto* size = entity_manager.getComponent<SizeComponent>(entityId, Size);
    //     auto* color = entity_manager.getComponent<ColorComponent>(entityId, Color);
    //     // auto* texture = entityManager->getComponent<PositionComp>(entityId, Position);
    //
    //     if (!position || !size || !color) return;
    //
    //     unsigned int vertexStartIndex  = vertices.size();
    //
    //     // if (!texture) {
    //     // shader.setBool("hasTexture", GL_FALSE);
    //     // glBindTexture(GL_TEXTURE_2D, 0);
    //     // } else {
    //     //     shader.setBool("hasTexture", GL_TRUE);
    //     //     texture->texture.bind();
    //     // }
    //
    //     vertices.push_back(Vertex{position->x, position->y, size->w, size->h, color->color, 0,0});
    //     // Sol üst köşe
    //     vertices.push_back(Vertex{position->x, position->y + size->h, size->w, size->h, color->color, 1,0});
    //     // Sağ alt köşe
    //     vertices.push_back(Vertex{position->x + size->w, position->y, size->w, size->h, color->color, 0,1});
    //     // Sağ üst köşe
    //     vertices.push_back(Vertex{position->x + size->w, position->y + size->h, size->w, size->h, color->color, 1, 1});
    //
    //     //unsigned int indices_offset = vertexCount * 4;
    //     //todo: check calculation here
    //     //unsigned int indices_offset = vertexStartIndex;
    //     unsigned int indices_offset = vertexCount;
    //
    //     indices.push_back(indices_offset);
    //     indices.push_back(indices_offset + 1);
    //     indices.push_back(indices_offset + 2);
    //     indices.push_back(indices_offset + 1);
    //     indices.push_back(indices_offset + 2);
    //     indices.push_back(indices_offset + 3);
    //
    //     // entity.setVertexOffset(vertexStartIndex);
    //     // entity.setIndicesOffset(indices.size() - 6);
    //
    //     vertexCount += 4;
    // }
}

unsigned int lastEntityCount = 0;
void Renderer::drawEntitiesBuffer() {
    shader.use();
    shader.setVec4("windowSize", windowSize);

    // vertices.clear();

    //for (auto& entityId : entityManager->entities) {addEntitiesBuffer(entityManager, entityId);}
    // auto maskSize = componentManager.getEntityMasks().size();
    if (vertices.empty() || componentManager.entitiesUpdated) {
        // lastEntityCount = componentManager.entityCount;
        componentManager.entitiesUpdated = false;
        // std::cout << "ENTITY COUNT CHANGED: " <<  componentManager.getEntityMasks().size() << std::endl;
        clear();
        addEntitiesBuffer();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data());
    }
    else {
        updateEntitiesVerticesBuffer();
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    // glBindVertexArray(0);


    // glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());
    // glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // // glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    // glBufferData(GL_ARRAY_BUFFER,  vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    //
    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    // // glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
    //
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    // glBindVertexArray(VAO);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    //glBindVertexArray(0);

    // clear();
}

std::vector<unsigned char> loadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open font file: " + filename);
    }

    // Dosyanın boyutunu belirle
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    if (length == 0) {
        throw std::runtime_error("Font file is empty: " + filename);
    }

    // Dosya içeriğini vektöre yükle
    std::vector<unsigned char> buffer(length);
    file.read(reinterpret_cast<char*>(buffer.data()), length);

    if (!file) {
        throw std::runtime_error("Failed to read font file: " + filename);
    }

    return buffer;
}


void Renderer::loadTextAtlas(const std::string& fontPath, unsigned int fontSize) {
    std::vector<unsigned char> fontData = loadFile(fontPath);

    stbtt_aligned_quad q;
    float cx = 0;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textAtlasTextureID);
    glBindTexture(GL_TEXTURE_2D, textAtlasTextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* bitmap = new unsigned char[512 * 512];
    std::cout << "FONT SIZE: " << fontData.size() << std::endl;
    std::cout << "FONT DATA: " << fontData.data() << std::endl;
    stbtt_BakeFontBitmap(fontData.data(), 0, fontSize, bitmap, 512, 512, 32, 96, cdata); // ASCII 32'den 127'ye (96 karakter)

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    delete[] bitmap;

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawText(const std::string& text, float x, float y, float scale, const vec4& color) {


    if (textAtlasTextureID == 0) {
        throw std::runtime_error("Text atlas texture is not initialized");
    }

    stbtt_aligned_quad q;
    float cx = x;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textAtlasTextureID);
    shader.use();
    shader.setFloat("hasTexture", true);
    shader.setVec4("windowSize", windowSize);
    shader.setInt("texture1", 0);

    for (char c : text) {
        if (c < 32 || c > 127) continue; // Sadece ASCII karakterleri işleyelim

        stbtt_GetBakedQuad(cdata, 512, 512, c - 32, &cx, &y, &q, false);

        float w = (q.x1 - q.x0) * scale;
        float h = (q.y1 - q.y0) * scale;

        // Dört köşe için Vertex nesnelerini oluştur
        // Vertex{x, position->y, size->w, size->h, color->color, 0,0}
        Vertex v1 = { q.x0, q.y1, w, h, color, q.s0, q.t0 };
        Vertex v2 = { q.x1, q.y1, w, h, color, q.s1, q.t0 };
        Vertex v3 = { q.x0, q.y0, w, h, color, q.s0, q.t1 };
        Vertex v4 = { q.x1, q.y0, w, h, color, q.s1, q.t1 };

        // Köşeleri vertices listesine ekle
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);

        // Üçgenler için indeksleri ekle
        indices.push_back(vertexCount + 0);
        indices.push_back(vertexCount + 1);
        indices.push_back(vertexCount + 2);
        indices.push_back(vertexCount + 1);
        indices.push_back(vertexCount + 3);
        indices.push_back(vertexCount + 2);

        // vertices.push_back(Vertex{x, y, w, h, color, q.s0, q.t0});
        // // Sol üst köşe
        // vertices.push_back(Vertex{x, y + h, w, h, color, q.s1, q.t0});
        // // Sağ alt köşe
        // vertices.push_back(Vertex{x + w, y, w, h, color, q.s1, q.t1});
        // // Sağ üst köşe
        // vertices.push_back(Vertex{x + w, y + h, w, h, color, q.s0, q.t1});

        // Köşeleri vertices listesine ekle
        // vertices.push_back(v1);
        // vertices.push_back(v2);
        // vertices.push_back(v3);
        // vertices.push_back(v4);
        //
        // // Üçgenler için indeksleri ekle
        // indices.push_back(vertexCount + 0);
        // indices.push_back(vertexCount + 1);
        // indices.push_back(vertexCount + 2);
        // indices.push_back(vertexCount + 1);
        // indices.push_back(vertexCount + 2);
        // indices.push_back(vertexCount + 3);

        vertexCount += 4;
    }

    // draw();

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    //
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    //
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
    //
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
    //
    // glBindTexture(GL_TEXTURE_2D, 0);
    //
    // // glDisable(GL_BLEND);
    // glBindVertexArray(0);
    //
    // clear();
}

void Renderer::drawEntities(std::vector<Entity>& entities, const float deltaTime) {
    shader.use();
    shader.setVec4("windowSize", windowSize);
    shader.setBool("gravityActive", true);
    shader.setFloat("gravityDeltaTime", deltaTime);

    if (vertexCount == 0 || lastEntityCount != entities.size()) {
        //todo: change here make it clever later
        //lastEntityCount = entities.size();
        //std::cerr << "No vertex buffer created" << std::endl;
        if (vertexCount == 0) {
            vertices.clear();
            indices.clear();

            for (auto& entity : entities) {addEntities(entity);}

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
            glBufferData(GL_ARRAY_BUFFER,  maxVertices * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
            //glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxVertices * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
        }
        else {
            //todo: afterwards write a entitymanager.........
            int diff = entities.size() - lastEntityCount;
            std::cout << "Diff count: " << diff << "Entitiy Size:" << entities.size() << "Last entity Count: " << lastEntityCount << std::endl;
            lastEntityCount = entities.size();
            for (int i = entities.size() - diff; i < entities.size(); i++) {
                addEntities(entities[i]);
            }

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
            //glBufferData(GL_ARRAY_BUFFER,  maxVertices * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
            glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,0, indices.size() * sizeof(unsigned int), indices.data());
            //glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxVertices * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
        }

        return;
    }

    //todo: check vertices size vs entitites size calculation
    // if (lastEntityCount != entities.size()) {
    //     int diff = entities.size() - lastEntityCount;
    //     lastEntityCount = entities.size();
    //     std::cout << "Diff count: " << diff << "Entitiy Size:" << entities.size() << "Last entity Count: " << lastEntityCount << std::endl;
    //     for (int i = entities.size() - diff; i < entities.size(); i++) {
    //         addEntities(entities[i]);
    //     }
    // }

    // unsigned int counter = 0;
    // unsigned int fullEntitySize = entities.size();
    // bool fullBufferUpdate = false;
    // //todo: maybe we can make if open check and not bind the buffer again
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // for (auto& entity : entities) {
    //     if (entity.isDirty()) {
    //         counter++;
    //
    //         if (!fullBufferUpdate && counter >= fullEntitySize * 0.0001) {
    //             fullBufferUpdate = true;
    //         }
    //
    //         if (!fullBufferUpdate) {
    //             unsigned int verticeOffset = entity.getVertexOffset();
    //             unsigned int byteOffset = verticeOffset * sizeof(Vertex);
    //             updateEntitiesVertices(entity, entity.getVertexOffset());
    //             glBufferSubData(GL_ARRAY_BUFFER, byteOffset, 4 * sizeof(Vertex), &vertices[verticeOffset]);
    //         }
    //
    //         // updateEntitiesVertices(entity, entity.getVertexOffset());
    //         // entity.updateCachedVersion();
    //         // dirtyEntities.push_back(entity);
    //         //updateEntitiesVertices(entity, entity.getVertexOffset());
    //         // if (counter > 50) {
    //         //     //todo: 50 bir threshold tum buffer paslansin mi degil mi diye
    //         //     glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    //         //     entity.updateCachedVersion();
    //         //     break;
    //         // }
    //         //
    //         // unsigned int verticeOffset = entity.getVertexOffset();
    //         // unsigned int byteOffset = verticeOffset * sizeof(Vertex);
    //         // //updateEntitiesVertices(entity, entity.getVertexOffset());
    //         // glBufferSubData(GL_ARRAY_BUFFER, byteOffset, 4 * sizeof(Vertex), &vertices[verticeOffset]);
    //         // entity.updateCachedVersion();
    //     }
    //
    //     if (fullBufferUpdate) {
    //         updateEntitiesVertices(entity, entity.getVertexOffset());
    //     }
    //
    //     entity.updateCachedVersion();
    // }

    // if (fullBufferUpdate) {
    //     //std::cout << "Full Update " << fullEntitySize << std::endl;
    //     glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    // }
    // else {
    //     for (auto& entity : dirtyEntities) {
    //         unsigned int verticeOffset = entity.getVertexOffset();
    //         unsigned int byteOffset = verticeOffset * sizeof(Vertex);
    //         //updateEntitiesVertices(entity, entity.getVertexOffset());
    //         glBufferSubData(GL_ARRAY_BUFFER, byteOffset, 4 * sizeof(Vertex), &vertices[verticeOffset]);
    //         // entity.updateCachedVersion();
    //     }
    // }
    // dirtyEntities.clear();

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // std::vector<Vertex> updatedVertices;
    // std::vector<unsigned int> updatedIndices;
    // unsigned int localVertexCount = 0;

    //vertices.clear();


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

    //todo: her seyi sil bastan yapabilir
    // if (!updatedVertices.empty()) {
    // }

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
