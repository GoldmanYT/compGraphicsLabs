#pragma once

#include "Data.h"
#include <fstream>

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