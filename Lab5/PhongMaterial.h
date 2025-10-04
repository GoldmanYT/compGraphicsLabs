#pragma once

#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include <fstream>
#include <iostream>

using namespace glm;
using namespace std;

extern std::string DIFFUSE_TEXT;
extern std::string AMBIENT_TEXT;
extern std::string SPECULAR_TEXT;
extern std::string EMISSION_TEXT;
extern std::string SHINESS_TEXT;

// ����� ��� ������ � ����������
class PhongMaterial {
public:
    // ����������� �� ���������
    PhongMaterial();
    // ������� ���������� ���������
    void setAmbient(vec4 color);
    void setDiffuse(vec4 color);
    void setSpecular(vec4 color);
    void setEmission(vec4 color);
    void setShininess(float p);
    // �������� ���������� ��������� �� �������� ���������� �����
    void load(std::string filename);
    // ��������� ���� ���������� ���������
    void apply();

private:
    // ������� ������������
    vec4 ambient;
    // ��������� ������������
    vec4 diffuse;
    // ���������� ������������
    vec4 specular;
    // ������������
    vec4 emission;
    // ������� ����������������
    float shininess;
};