#ifndef TEXTURE_H
#define TEXTURE_H

class texture2D
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int id;
    // texture image dimensions
    unsigned int width, height; // width and height of loaded image in pixels
    // texture Format
    unsigned int internal_Format; // format of texture object
    unsigned int image_Format; // format of loaded image
    // texture configuration
    unsigned int wrap_S; // wrapping mode on S axis
    unsigned int wrap_T; // wrapping mode on T axis
    unsigned int filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int filter_Max; // filtering mode if texture pixels > screen pixels
    // constructor (sets default texture modes)
    texture2D();
    // generates texture from image data
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;
};


#endif