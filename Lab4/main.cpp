#include <windows.h>

#include <iostream>

#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include <vector>

#include "Camera.h"
#include "GraphicObject.h"

// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;

vector<GraphicObject> graphicObjects;
Camera camera;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // установить матрицу проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);

    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.apply();

    for (auto& go : graphicObjects) {
        go.draw();
        // glutWireTeapot(1.0);
    }

    // смена переднего и заднего буферов
    glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value)
{
    // устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
    // эта же функция будет вызвана еще раз через 20 мс
    glutTimerFunc(20, simulation, 0);
    camera.apply();
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
    printf("Key code is %i\n", key);

    switch (static_cast<char>(key)) {
    case 'w':
        cout << "rotateUp\n";
        camera.rotateUpDown(5.0);
        break;
    case 's':
        camera.rotateUpDown(-5.0);
        break;
    case 'a':
        camera.rotateLeftRight(5.0);
        break;
    case 'd':
        camera.rotateLeftRight(-5.0);
        break;
    case '+':
        camera.zoomInOut(0.2);
        break;
    case '-':
        camera.zoomInOut(-0.2);
        break;
    }
    vec3 position = camera.getPosition();
    printf("X: %f, Y: %f, Z: %f\n", position.x, position.y, position.z);
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");

    // инициализация библиотеки GLUT
    glutInit(&argc, argv);
    // инициализация дисплея (формат вывода)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    // СОЗДАНИЕ ОКНА:
    // 1. устанавливаем верхний левый угол окна
    glutInitWindowPosition(200, 200);
    // 2. устанавливаем размер окна
    glutInitWindowSize(800, 600);
    // 3. создаем окно
    glutCreateWindow("Laba_04");

    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию, которая будет вызвана через 20 мс
    glutTimerFunc(20, simulation, 0);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    glutKeyboardFunc(keyboardFunc);

    GraphicObject tempGraphicObject;
    // инициализация графических объектов
    // 1 -----------------------------------------
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 2 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270);
    tempGraphicObject.setСolor(vec3(0, 1, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 3 -----------------------------------------
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0);
    tempGraphicObject.setСolor(vec3(0, 0, 1));
    graphicObjects.push_back(tempGraphicObject);
    // 4 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90);
    tempGraphicObject.setСolor(vec3(1, 1, 1));
    graphicObjects.push_back(tempGraphicObject);

    camera.setPosition(vec3(10, 15, 17.5));

    // основной цикл обработки сообщений ОС
    glutMainLoop();

    return 0;
};