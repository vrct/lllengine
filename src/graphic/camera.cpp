#include "camera.h"

Camera::Camera(){};

Camera::Camera(vec4 _position, vec4 _viewPort, float _zoom, vec4 _rotation)
{
    this->position = _position;
    this->viewPort = _viewPort;
    this->zoom = _zoom;
    this->rotation = _rotation;
    calculateMatrix();
}

Camera::~Camera()
{

}

void Camera::calculateMatrix()
{
    float halfWidth = viewPort.x / 2.0f / zoom;
    float halfHeight = viewPort.y / 2.0f / zoom;

    //projectionMatrix = matrix4().orthographic(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
    projectionMatrix = matrix4().orthographic(0, viewPort.x, viewPort.y, 0,  -1.0f, 1.0f);

    viewMatrix = matrix4().identity();
    vec4 translateVec = vec4(position.x, -position.y, 0); 
    vec4 scaleVec = vec4(zoom, zoom, 1); 

    viewMatrix.translateMatrix(translateVec);
    viewMatrix.scaleMatrix(scaleVec);
    //todo: rotationmatrix to be added
}

matrix4 Camera::getUpdatedMatrix()
{
    std::cout << "PROJECTION M: " << std::endl << projectionMatrix << std::endl << "VIEW M:" << std::endl << viewMatrix << std::endl;
    return projectionMatrix * viewMatrix;
}

void Camera::move(vec4 moveAmount, float speed = 1)
{
    position.x = (position.x + moveAmount.normalize().x) * speed;
    position.y = (position.y + moveAmount.normalize().y) * speed;
    position.z = (position.z + moveAmount.normalize().z) * speed;
}

void Camera::setLookAt()
{

}

void Camera::setZoom(float _zoom)
{
    zoom += _zoom;
}

void Camera::setRotation(vec4 _rotation)
{
    rotation = rotation + _rotation;
}