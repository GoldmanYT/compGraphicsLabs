#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>
#include <windows.h>

// используем пространство имен стандартной библиотеки
using namespace std;

struct Color {
    double r, g, b;
};

Color BLACK = { 0.0, 0.0, 0.0 };
Color WHITE = { 1.0, 1.0, 1.0 };
Color BLUE = { 0.0, 0.0, 1.0 };
Color RED = { 1.0, 0.0, 0.0 };
Color PURPLE = { 1.0, 0.0, 1.0 };

array<Color, 5> colors = { BLACK, WHITE, BLUE, RED, PURPLE };
size_t colorIndex = 0;

enum Mode {
    ON_KEY_PRESS,
    ON_TIME
};

Mode mode = ON_KEY_PRESS;

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

    Color color = colors[colorIndex];

    glColor3f(color.r, color.g, color.b);
    glutWireTeapot(1.0);

    // смена переднего и заднего буферов
    glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value)
{
    if (mode == ON_TIME) {
        colorIndex = (++colorIndex) % colors.size();
        // устанавливаем признак того, что окно нуждается в перерисовке
        glutPostRedisplay();
        // эта же функция будет вызвана еще раз через 20 мс
        glutTimerFunc(1000, simulation, 0);
    }
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
    if (mode == ON_KEY_PRESS) {
        colorIndex = (++colorIndex) % colors.size();
    }
    glutPostRedisplay();
};

void main(int argc, char** argv)
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
};