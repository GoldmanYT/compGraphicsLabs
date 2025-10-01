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
    // ���������� ������ - ���������� �� ������ ������� ��������� �� �������� �������
    r = length(position);
    // ���������� ������������ ����:
    // ��� ���� ����� �������� �� ������ ��������� � ����������� (v1)
    // � ��������� ����� ������� �� �������������� ��������� (v2)
    // ��� ����������� ���� ������������ ��������� ������������ ��������������� ��������
    vec3 v1 = position;
    vec3 v2 = vec3(v1.x, 0, v1.z);
    float cos_y = dot(normalize(v1), normalize(v2));
    angleY = degrees(acos(cos_y));
    // ����������� ������� ���������� �������������� ����:
    // ��� ���� ����� ��������� (v2) � ��������� �������� ����� ��� Ox
    float cos_x = dot(normalize(v2), vec3(1, 0, 0));
    angleX = degrees(acos(cos_x));
    // ������������� ������� (��� ������������� ������ ����������)
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
