#ifndef CAMERA_H
#define CAMERA_H

#include "matrix4.h"

struct Camera
{
    private:
        vec4 position;
        vec4 viewPort;
        vec4 rotation;
        vec4 lookAt;
        float zoom;


    public:
        matrix4 projectionMatrix;
        matrix4 viewMatrix;

        Camera();
        ~Camera();
        Camera(vec4 _position, vec4 _viewPort, float _zoom = 1, vec4 _rotation = vec4());
        void calculateMatrix();
        matrix4 getUpdatedMatrix();
        void move(vec4, float);
        void setLookAt();
        void setZoom(float zoom);
        void setRotation(vec4);
};

#endif