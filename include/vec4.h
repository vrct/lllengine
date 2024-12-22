#ifndef VEC4_H
#define VEC4_H

#include "math.h"
#include <iostream>
#include "GL/glew.h"

#define threshold  1e-5

struct vec4
{
    union {
        struct { float x, y, z, w; }; // Doğrudan erişim
        float elements[4];            // Array olarak erişim
    };
    //float &x, &y, &z, &w;
    //GLfloat elements[4];

    vec4(float x0 = 0, float y0 = 0, float z0 = 0, float w0 = 1) :
        x(elements[0]), y(elements[1]), z(elements[2]), w(elements[3])
    {
       x = x0; 
       y = y0; 
       z = z0; 
       w = w0; 
    }

    vec4 zero() 
    {
        return vec4();
    }

    vec4 identity()
    {
        return vec4(1, 1, 1, 1);
    }

    vec4 negate()
    {
        return *this * -1;
    }

    double length()
    {
        return sqrt((pow(x, 2) + pow(y, 2) + pow(z, 2)));
    }

    vec4 normalize()
    {
        return (*this / length());
    }

    double dot(vec4 val)
    {
        return x * val.x + y * val.y + z * val.z;
    }

    vec4 cross(vec4 val)
    {
        return vec4((y * val.z - z * val.y), (z * val.x - x * val.z), (x * val.y - y * val.x));
    }

    double angle(vec4 val)
    {
        double cosTheta = dot(val) / (length() * val.length());
        double angleRadians = acos(cosTheta);
        double angleDegrees = angleRadians * (180.0 / (atan(1) * 4));
        return angleDegrees;
    }

/*
    double dot(vec4 val)
    {
        return cos(length() * val.length());
    }
*/
    vec4 operator+ (int const& val)
    {
        vec4 result;
        result.x = x + val;
        result.y = y + val;
        result.z = z + val;

        return result;
        //w is reserved if needed add
    }

    vec4 operator+ (vec4 const& val)
    {
        vec4 result;
        result.x = x + val.x;
        result.y = y + val.y;
        result.z = z + val.z;

        return result;
        //w is reserved if needed add
    }

    vec4 operator- (int const& val)
    {
        vec4 result;
        result.x = x - val;
        result.y = y - val;
        result.z = z - val;
        return result;
        //w is reserved if needed add
    }

    vec4 operator- (vec4 const& val)
    {
        vec4 result;
        result.x = x - val.x;
        result.y = y - val.y;
        result.z = z - val.z;
        return result;
        //w is reserved if needed add
    }

    vec4 operator* (int const& val)
    {
        vec4 result;
        result.x = x * val;
        result.y = y * val;
        result.z = z * val;
        return result;
        //w is reserved if needed add
    }

    vec4 operator* (vec4 const& val)
    {
        vec4 result;
        result.x = x * val.x;
        result.y = y * val.y;
        result.z = z * val.z;
        return result;
        //w is reserved if needed add
    }


    vec4 operator/ (int const& val)
    {
        vec4 result;
        result.x = x / val;
        result.y = y / val;
        result.z = z / val;
        return result;
        //w is reserved if needed add
    }

    vec4 operator/ (vec4 const& val)
    {
        vec4 result;
        result.x = x / val.x;
        result.y = y / val.y;
        result.z = z / val.z;
        return result;
        //w is reserved if needed add
    }

    vec4& operator= (vec4 const& val)
    {
        if(this != &val)
        {
            x = val.x;
            y = val.y;
            z = val.z;
            w = val.w;
        }

        return *this;
    }


    const GLfloat* data() const {
        return elements;
    }

    friend std::ostream& operator<<(std::ostream& os, const vec4& v) {
        os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
        return os;
    }
};


#endif