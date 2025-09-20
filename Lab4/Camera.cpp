#include "Camera.h"

Camera::Camera()
    : r(25)
    , angleX(1.05)
    , angleY(0.64)
{
    recalculatePosition();
}

Camera::Camera(vec3 position)
{
    setPosition(position);
}

Camera::Camera(float x, float y, float z)
{
    setPosition(vec3(x, y, z));
}

void Camera::setPosition(vec3 position)
{
    angleX = atan2(position.z, position.x);
    float hypotXZ = hypotf(position.z, position.x);
    angleY = atan2(position.y, hypotXZ);
    r = hypotf(position.y, hypotXZ);

    recalculatePosition();
}

vec3 Camera::getPosition()
{
    return position;
}

void Camera::rotateLeftRight(float degree)
{
    angleX += radians(degree);
    recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
    angleY -= radians(degree);
    recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
    r -= distance;
    if (r < 1e-3) {
        r = 1e-3;
    }
    recalculatePosition();
}

void Camera::apply()
{
    gluLookAt(
        position.x, position.y, position.z,
        0, 0, 0,
        0, 1, 0);
}

void Camera::recalculatePosition()
{
    position.x = r * cosf(angleX);
    position.z = r * sinf(angleX);
    float hypotXZ = hypotf(position.x, position.z);
    position.y = r * sinf(angleY);
}
