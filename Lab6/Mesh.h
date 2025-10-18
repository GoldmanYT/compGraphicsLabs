#pragma once

#include "../glm/glm.hpp"
#include "GL/freeglut.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <array>

using namespace std;
using namespace glm;

// Структура, описывающая одну вершину полигональной сетки
// каждая вершина имеет геометрические координаты,
// вектор нормали и текстурные координаты
struct Vertex {
    Vertex(vec3 v, vec3 n, vec2 t)
        : coord()
        , normal()
        , texCoord()
    {
        for (int i = 0; i < 3; ++i) {
            coord[i] = v[i];
            normal[i] = n[i];
            if (i < 2) {
                texCoord[i] = t[i];
            }
        }
    }

    // геометрические координаты
    GLfloat coord[3];
    // вектор нормали
    GLfloat normal[3];
    // текстурные координаты нулевого текстурного блока
    GLfloat texCoord[2];
};

// КЛАСС ДЛЯ РАБОТЫ C МЕШЕМ
class Mesh {
public:
    // конструктор
    Mesh();
    // загрузка меша из файла с указанным именем
    void load(string filename);
    // вывод меша (передача всех вершин в OpenGL)
    void draw();

private:
    // массив вершин полигональной сетки
    vector<Vertex> vertices;
};