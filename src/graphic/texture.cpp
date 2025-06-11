#include "texture.h"
#include "GL/glew.h"

texture2D::texture2D()
    : width(0), height(0), internal_Format(GL_RGB), image_Format(GL_RGB), wrap_S(GL_CLAMP_TO_EDGE), wrap_T(GL_CLAMP_TO_EDGE), filter_Min(GL_NEAREST), filter_Max(GL_NEAREST)
{
    glGenTextures(1, &this->id);
}

void texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_Format, width, height, 0, this->image_Format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_Max);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}