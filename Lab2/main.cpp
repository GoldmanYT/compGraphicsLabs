#include <windows.h>

#include <iostream>

#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include <vector>

// ���������� ������������ ���� ����������� ����������
using namespace std;
using namespace glm;

vector<vec3> teapotColors = { { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 1, 1, 0 }, { 1.0f / 2, 0, 1 } };
double currentTime = 0;

size_t getColorIndex()
{
    return size_t(currentTime);
}

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

    size_t colorIndex = getColorIndex();
    glColor3f(teapotColors[colorIndex][0], teapotColors[colorIndex][1], teapotColors[colorIndex][2]);
    glutWireTeapot(1.0);

    // ����� ��������� � ������� �������
    glutSwapBuffers();
};

// ������� ���������� ������ 20 ��
void simulation(int value)
{
    // ������������� ������� ����, ��� ���� ��������� � �����������
    glutPostRedisplay();
    // ��� �� ������� ����� ������� ��� ��� ����� 20 ��
    glutTimerFunc(20, simulation, 0);

    currentTime += 0.02;
    if (currentTime >= teapotColors.size()) {
        currentTime -= teapotColors.size();
    }
};

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
    printf("Key code is %i\n", key);
};

int main(int argc, char** argv)
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

    return 0;
};