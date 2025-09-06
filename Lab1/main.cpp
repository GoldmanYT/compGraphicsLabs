#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>
#include <windows.h>

// ���������� ������������ ���� ����������� ����������
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

// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
    // ���������� ����� ������� ���������, ������ ���� ������� ����
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // ���������� ������� �������� � ���������� ��������
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
    // �������� ����� ����� � ����� �������
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �������� ���� �������
    glEnable(GL_DEPTH_TEST);

    // ������������� ������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

    Color color = colors[colorIndex];

    glColor3f(color.r, color.g, color.b);
    glutWireTeapot(1.0);

    // ����� ��������� � ������� �������
    glutSwapBuffers();
};

// ������� ���������� ������ 20 ��
void simulation(int value)
{
    if (mode == ON_TIME) {
        colorIndex = (++colorIndex) % colors.size();
        // ������������� ������� ����, ��� ���� ��������� � �����������
        glutPostRedisplay();
        // ��� �� ������� ����� ������� ��� ��� ����� 20 ��
        glutTimerFunc(1000, simulation, 0);
    }
};

// ������� ��������� ������� ������
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

    // ������������� ���������� GLUT
    glutInit(&argc, argv);
    // ������������� ������� (������ ������)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    // �������� ����:
    // 1. ������������� ������� ����� ���� ����
    glutInitWindowPosition(200, 200);
    // 2. ������������� ������ ����
    glutInitWindowSize(800, 600);
    // 3. ������� ����
    glutCreateWindow("Laba_01");

    // ��������� ������� ��������� ������
    // ������������� �������, ������� ����� ���������� ��� ����������� ����
    glutDisplayFunc(display);
    // ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
    glutReshapeFunc(reshape);
    // ������������� �������, ������� ����� ������� ����� 20 ��
    glutTimerFunc(20, simulation, 0);
    // ������������� �������, ������� ����� ���������� ��� ������� �� �������
    glutKeyboardFunc(keyboardFunc);

    // �������� ���� ��������� ��������� ��
    glutMainLoop();
};