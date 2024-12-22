#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "matrix4.h"

class Shader
{
    public:
        //shader program ID
        unsigned int ID;
        Shader();
        Shader(const char* vertexPath, const char* fragmentPath);

        // use program (activate shader)
        void use();
        void deleteProgram();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMatrix4(const std::string &name, matrix4 value) const;
        void setVec4(const std::string &name, vec4 mat) const;
};

#endif
