#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <memory>
#include <stdio.h>
#include <windows.h>

#include "Mesh.h"
#include "PhongMaterial.h"

using namespace glm;

extern string COORD_TEXT;
extern string NORMAL_TEXT;
extern string TEX_COORD_TEXT;
extern string FACE_TEXT;

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject {
public:
    // Конструктор
    GraphicObject();

    // Установка и получение позиции объекта
    void setPosition(vec3 position);
    vec3 getPosition();

    // Установка и получения угла поворота в градусах
    // поворот осуществляется в горизонтальной плоскости
    // вокруг оси Oy по часовой стрелке
    void setAngle(float grad);
    float getAngle();

    // Установка текущего цвета объекта
    void setColor(vec3 color);
    vec3 getColor();

    // Установка используемого материала
    void setMaterial(std::shared_ptr<PhongMaterial> material);
    // Установка используемого меша
    void setMesh(std::shared_ptr<Mesh> mesh);

    // Вывести объект
    void draw();

private:
    // Позиция объекта в глобальной системе координат
    vec3 position;
    // Угол поворота в горизонтальной плоскости (в градусах)
    float angle;
    // Цвет модели
    vec3 color;
    // Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
    mat4 modelMatrix;
    // Используемый материал
    std::shared_ptr<PhongMaterial> material;
    // Используемый меш
    std::shared_ptr<Mesh> mesh;

private:
    // расчет матрицы modelMatrix на основе position и angle
    void recalculateModelMatrix();
};