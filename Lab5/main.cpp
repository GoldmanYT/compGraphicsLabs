#include <iostream>
#include <vector>
#include <windows.h>

#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera.h"
#include "Data.h"
#include "Display.h"
#include "GraphicObject.h"
#include "Simulation.h"

// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;

int main(int argv, char** argc)
{
    setlocale(LC_ALL, "ru");

    // инициализация библиотеки GLUT
    glutInit(&argv, argc);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    // включаем режим расчета освещения
    glEnable(GL_LIGHTING);
    // включаем нулевой источник света
    glEnable(GL_LIGHT0);

    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(200, 200);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Lab_04");

    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию, которая будет вызываться постоянно
    glutIdleFunc(simulation);

    initData();

    // основной цикл обработки сообщений ОС
    glutMainLoop();

    return 0;
};