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
#include <memory>

#include "PhongMaterial.h"

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
    void setAngle(float grad);
    float getAngle();
    // ��������� �������� ����� �������
    void setColor(vec3 color);
    vec3 getColor();
    // ��������� ������������� ���������
    void setMaterial(std::shared_ptr<PhongMaterial> material);
    // ������� ������
    void draw();

private:
    // ������� ������� � ���������� ������� ���������
    vec3 position;
    // ���� �������� � �������������� ��������� (� ��������)
    float angle;
    // ���� ������
    vec3 color;
    // ������� ������ (������������ �������) - ���� �� ��������� ������ ���
    mat4 modelMatrix;
    // ������������ ��������
    std::shared_ptr<PhongMaterial> material;

private:
    // ������ ������� modelMatrix �� ������ position � angle
    void recalculateModelMatrix();
};