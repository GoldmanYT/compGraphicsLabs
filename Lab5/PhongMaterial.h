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

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial {
public:
    // конструктор по умолчанию
    PhongMaterial();
    // задание параметров материала
    void setAmbient(vec4 color);
    void setDiffuse(vec4 color);
    void setSpecular(vec4 color);
    void setEmission(vec4 color);
    void setShininess(float p);
    // загрузка параметров материала из внешнего текстового файла
    void load(std::string filename);
    // установка всех параметров материала
    void apply();

private:
    // фоновая составляющая
    vec4 ambient;
    // диффузная составляющая
    vec4 diffuse;
    // зеркальная составляющая
    vec4 specular;
    // самосвечение
    vec4 emission;
    // степень отполированности
    float shininess;
};