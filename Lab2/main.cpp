#include <windows.h>

#include <iostream>

#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include <vector>

// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;

vector<vec3> teapotColors = { { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0.5f, 0, 1 } };
double currentTime = 0;

size_t getColorIndex()
{
    return size_t(currentTime);
}

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
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);

    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

    size_t colorIndex = getColorIndex();
    glColor3f(teapotColors[colorIndex][0], teapotColors[colorIndex][1], teapotColors[colorIndex][2]);
    glutWireTeapot(1.0);

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

    currentTime += 0.02;
    if (currentTime >= teapotColors.size()) {
        currentTime -= teapotColors.size();
    }
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
    printf("Key code is %i\n", key);
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
    glutCreateWindow("Laba_01");

    // УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
    // устанавливаем функцию, которая будет вызываться для перерисовки окна
    glutDisplayFunc(display);
    // устанавливаем функцию, которая будет вызываться при изменении размеров окна
    glutReshapeFunc(reshape);
    // устанавливаем функцию, которая будет вызвана через 20 мс
    glutTimerFunc(20, simulation, 0);
    // устанавливаем функцию, которая будет вызываться при нажатии на клавишу
    glutKeyboardFunc(keyboardFunc);

    // основной цикл обработки сообщений ОС
    glutMainLoop();

    return 0;
};