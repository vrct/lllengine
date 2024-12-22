#ifndef MATRIX_H
#define MATRIX_H

#include "vec4.h"
#include <iostream>
#include "GL/glew.h"

struct matrix4
{
    float &x0, &x1, &x2, &x3;
    float &y0, &y1, &y2, &y3;
    float &z0, &z1, &z2, &z3;
    float &w0, &w1, &w2, &w3;

    GLfloat elements[16];

    matrix4(float _x0 = 0, float _x1 = 0, float _x2 = 0, float _x3 = 0, float _y0 = 0, float _y1 = 0, float _y2 = 0, float _y3 = 0, float _z0 = 0, float _z1 = 0, float _z2 = 0, float _z3 = 0, float _w0 = 0, float _w1 = 0, float _w2 = 0, float _w3 = 0) :
        x0(elements[0]), x1(elements[4]), x2(elements[8]), x3(elements[12]),
        y0(elements[1]), y1(elements[5]), y2(elements[9]), y3(elements[13]),
        z0(elements[2]), z1(elements[6]), z2(elements[10]), z3(elements[14]),
        w0(elements[3]), w1(elements[7]), w2(elements[11]), w3(elements[15]) 
    {
        //std::fill(elements.begin(), elements.end(), 0.0f);  // Set all to 0.0f first

        x0 = _x0;
        x1 = _x1;
        x2 = _x2;
        x3 = _x3;

        y0 = _y0;
        y1 = _y1;
        y2 = _y2;
        y3 = _y3;

        z0 = _z0;
        z1 = _z1;
        z2 = _z2;
        z3 = _z3;

        w0 = _w0;
        w1 = _w1;
        w2 = _w2;
        w3 = _w3;
    }

    matrix4 identity()
    {
        matrix4 result;

        result.x0 = 1;
        result.y1 = 1;
        result.z2 = 1;
        result.w3 = 1;

        return result;
    }


    matrix4 operator+ (matrix4 const& val)
    {
        matrix4 result;

        result.x0 = x0 + val.x0;
        result.x1 = x1 + val.x1;
        result.x2 = x2 + val.x2;
        result.x3 = x3 + val.x3;

        result.y0 = y0 + val.y0;
        result.y1 = y1 + val.y1;
        result.y2 = y2 + val.y2;
        result.y3 = y3 + val.y3;

        result.z0 = z0 + val.z0;
        result.z1 = z1 + val.z1;
        result.z2 = z2 + val.z2;
        result.z3 = z3 + val.z3;

        result.w0 = w0 + val.w0;
        result.w1 = w1 + val.w1;
        result.w2 = w2 + val.w2;
        result.w3 = w3 + val.w3;

        return result; 
    }


    matrix4 operator- (matrix4 const& val)
    {
        matrix4 result;

        result.x0 = x0 - val.x0;
        result.x1 = x1 - val.x1;
        result.x2 = x2 - val.x2;
        result.x3 = x3 - val.x3;

        result.y0 = y0 - val.y0;
        result.y1 = y1 - val.y1;
        result.y2 = y2 - val.y2;
        result.y3 = y3 - val.y3;

        result.z0 = z0 - val.z0;
        result.z1 = z1 - val.z1;
        result.z2 = z2 - val.z2;
        result.z3 = z3 - val.z3;

        result.w0 = w0 - val.w0;
        result.w1 = w1 - val.w1;
        result.w2 = w2 - val.w2;
        result.w3 = w3 - val.w3;

        return result; 
    }

    matrix4 operator* (float const& val)
    {
        matrix4 result;

        result.x0 = x0 * val;
        result.x1 = x1 * val;
        result.x2 = x2 * val;
        result.x3 = x3 * val;

        result.y0 = y0 * val;
        result.y1 = y1 * val;
        result.y2 = y2 * val;
        result.y3 = y3 * val;

        result.z0 = z0 * val;
        result.z1 = z1 * val;
        result.z2 = z2 * val;
        result.z3 = z3 * val;

        result.w0 = w0 * val;
        result.w1 = w1 * val;
        result.w2 = w2 * val;
        result.w3 = w3 * val;

        return result; 
    }

    matrix4 operator* (int const& val)
    {
        matrix4 result;

        result.x0 = x0 * val;
        result.x1 = x1 * val;
        result.x2 = x2 * val;
        result.x3 = x3 * val;

        result.y0 = y0 * val;
        result.y1 = y1 * val;
        result.y2 = y2 * val;
        result.y3 = y3 * val;

        result.z0 = z0 * val;
        result.z1 = z1 * val;
        result.z2 = z2 * val;
        result.z3 = z3 * val;

        result.w0 = w0 * val;
        result.w1 = w1 * val;
        result.w2 = w2 * val;
        result.w3 = w3 * val;

        return result; 
    }

    matrix4 operator* (matrix4 const& val)
    {
        matrix4 result;

        result.x0 = x0 * val.x0 + x1 * val.y0 + x2 * val.z0 + x3 * val.w0;
        result.x1 = x0 * val.x1 + x1 * val.y1 + x2 * val.z1 + x3 * val.w1;
        result.x2 = x0 * val.x2 + x1 * val.y2 + x2 * val.z2 + x3 * val.w2;
        result.x3 = x0 * val.x3 + x1 * val.y3 + x2 * val.z3 + x3 * val.w3;

        result.y0 = y0 * val.x0 + y1 * val.y0 + y2 * val.z0 + y3 * val.w0;
        result.y1 = y0 * val.x1 + y1 * val.y1 + y2 * val.z1 + y3 * val.w1;
        result.y2 = y0 * val.x2 + y1 * val.y2 + y2 * val.z2 + y3 * val.w2;
        result.y3 = y0 * val.x3 + y1 * val.y3 + y2 * val.z3 + y3 * val.w3;

        result.z0 = z0 * val.x0 + z1 * val.y0 + z2 * val.z0 + z3 * val.w0;
        result.z1 = z0 * val.x1 + z1 * val.y1 + z2 * val.z1 + z3 * val.w1;
        result.z2 = z0 * val.x2 + z1 * val.y2 + z2 * val.z2 + z3 * val.w2;
        result.z3 = z0 * val.x3 + z1 * val.y3 + z2 * val.z3 + z3 * val.w3;

        result.w0 = w0 * val.x0 + w1 * val.y0 + w2 * val.z0 + w3 * val.w0;
        result.w1 = w0 * val.x1 + w1 * val.y1 + w2 * val.z1 + w3 * val.w1;
        result.w2 = w0 * val.x2 + w1 * val.y2 + w2 * val.z2 + w3 * val.w2;
        result.w3 = w0 * val.x3 + w1 * val.y3 + w2 * val.z3 + w3 * val.w3;

        return result; 
    }

    matrix4& operator= (matrix4 const& val)
    {
        if(this != &val)
        {
            x0 = val.x0;
            x1 = val.x1;
            x2 = val.x2;
            x3 = val.x3;

            y0 = val.y0;
            y1 = val.y1;
            y2 = val.y2;
            y3 = val.y3;

            z0 = val.z0;
            z1 = val.z1;
            z2 = val.z2;
            z3 = val.z3;

            w0 = val.w0;
            w1 = val.w1;
            w2 = val.w2;
            w3 = val.w3;
        }

        return *this;
    }

    vec4 operator* (vec4 const& val)
    {
        vec4 result;
        result.x = x0 * val.x + x1 * val.y + x2 * val.z + x3 * val.w;  // result.x
        result.y = y0 * val.x + y1 * val.y + y2 * val.z + y3 * val.w;  // result.y
        result.z = z0 * val.x + z1 * val.y + z2 * val.z + z3 * val.w;  // result.z
        result.w = w0 * val.x + w1 * val.y + w2 * val.z + w3 * val.w;  // result.w
        return result; 
    }

    matrix4 rotationX(float angle)
    {
        matrix4 result = identity();

        float angleDegree = angle * M_PI / 180.0;

        result.y1 = checkPrecision(cos(angleDegree));
        result.y2 = checkPrecision(-sin(angleDegree));
        result.z1 = checkPrecision(sin(angleDegree));
        result.z2 = checkPrecision(cos(angleDegree));

        return result;
    }

    matrix4 rotationY(float angle)
    {
        matrix4 result = identity();

        float angleDegree = angle * M_PI / 180.0;

        result.x0 = checkPrecision(cos(angleDegree));
        result.x2 = checkPrecision(sin(angleDegree));
        result.z0 = checkPrecision(-sin(angleDegree));
        result.z2 = checkPrecision(cos(angleDegree));

        return result;
    }

    matrix4 rotationZ(float angle)
    {
        matrix4 result = identity();

        float angleDegree = angle * M_PI / 180.0;

        result.x0 = checkPrecision(cos(angleDegree));
        result.x1 = checkPrecision(-sin(angleDegree));
        result.y0 = checkPrecision(sin(angleDegree));
        result.y1 = checkPrecision(cos(angleDegree));

        return result;
    }

    matrix4 orthographic(float left, float right, float bottom, float top, float near, float far) {
        matrix4 result;

        // Main diagonal elements
        result.elements[0 + 0 * 4] = 2.0f / (right - left);
        result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
        result.elements[2 + 2 * 4] = -2.0f / (far - near);

        // Last column elements
        result.elements[0 + 3 * 4] = -(right + left) / (right - left);
        result.elements[1 + 3 * 4] = -(top + bottom) / (top - bottom);
        result.elements[2 + 3 * 4] = -(far + near) / (far - near);
        result.elements[3 + 3 * 4] = 1.0f;

        return result; 
    }

    void translateMatrix(vec4 translateVector)
    {
        x3 += translateVector.x;
        y3 += translateVector.y;
        z3 += translateVector.z;
    }

    void scaleMatrix(vec4 scaleVector)
    {
        x0 *= scaleVector.x;
        y1 *= scaleVector.y;
        z2 *= scaleVector.z;
    }

    //todo: move to math.utils
    float checkPrecision(float result)
    {
        if (std::abs(result) < threshold) {
            result = 0.0;
        }

        return result;
    }

    const GLfloat* data() const {
        return elements;
    }

    friend std::ostream& operator<<(std::ostream& os, const matrix4& v) {
        os << std::endl << 
        '(' << v.x0 << ", " << v.x1 << ", " << v.x2 << ", " << v.x3 << ')' << std::endl <<
        '(' << v.y0 << ", " << v.y1 << ", " << v.y2 << ", " << v.y3 << ')' << std::endl <<
        '(' << v.z0 << ", " << v.z1 << ", " << v.z2 << ", " << v.z3 << ')' << std::endl <<
        '(' << v.w0 << ", " << v.w1 << ", " << v.w2 << ", " << v.w3 << ')' << std::endl;
        return os;
    }

    //todo: create computeMatrix method in sprite to get combined translate, scale, and rotation matrixes
};

#endif