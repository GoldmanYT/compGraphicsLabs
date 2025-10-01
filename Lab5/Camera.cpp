#include "Camera.h"

using namespace std;

Camera::Camera()
    : r(25)
    , angleX(1.05f)
    , angleY(0.64f)
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
    // определяем радиус - расстояние от начала системы координат до заданной позиции
    r = length(position);
    // определяем вертикальный угол:
    // это угол между вектором из начала координат к наблюдателю (v1)
    // и проекцией этого вектора на горизонтальную плоскость (v2)
    // для определения угла используется скалярное произведение нормализованных векторов
    vec3 v1 = position;
    vec3 v2 = vec3(v1.x, 0, v1.z);
    float cos_y = dot(normalize(v1), normalize(v2));
    angleY = degrees(acos(cos_y));
    // аналогичным образом определяем горизонтальный угол:
    // это угол между проекцией (v2) и единичным вектором вдоль оси Ox
    float cos_x = dot(normalize(v2), vec3(1, 0, 0));
    angleX = degrees(acos(cos_x));
    // пересчитываем позицию (для корректировок ошибок округления)
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
    if (r < 1e-3f) {
        r = 1e-3f;
    }
    recalculatePosition();
}

void Camera::apply()
{
    gluLookAt(
        position.x, position.y, position.z,
        0, 0, 0,
        0, 1 - 2 * ((long long)floor(angleY / acos(-1)) % 2 != 0), 0);
}

void Camera::recalculatePosition()
{
    position.x = r * sin(angleX) * sin(angleY);
    position.y = r * cos(angleY);
    position.z = r * cos(angleX) * sin(angleY);
}
