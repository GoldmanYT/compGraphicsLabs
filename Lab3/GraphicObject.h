#pragma once

#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace glm;

// ����� ��� ������������� ������ ������������ �������
class GraphicObject {
public:
    // �����������
    GraphicObject();
    // ��������� � ��������� ������� �������
    void setPosition(vec3 position);
    vec3 getPosition();
    // ��������� � ��������� ���� �������� � ��������
    // ������� �������������� � �������������� ���������
    // ������ ��� Oy �� ������� �������
    void setAngle(float angle);
    float getAngle();
    // ��������� �������� ����� �������
    void set�olor(vec3 color);
    vec3 getColor();
    // ������� ������
    void draw();

private:
    // ������� ������� � ���������� ������� ���������
    vec3 position;
    // ���� �������� � �������������� ��������� (� ��������)
    float angle;
    // ���� ������
    vec3 color;
    // ������� ������ - ���� �� ��������� ������ ���
    mat4 modelMatrix;

private:
    // ������ ������� modelMatrix �� ������ position � angle
    void recalculateModelMatrix();
};