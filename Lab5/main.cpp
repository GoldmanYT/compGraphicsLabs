#include <iostream>
#include <vector>
#include <windows.h>

#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <GL/gl.h>
#include <GL/glu.h>

#include "Data.h"
#include "Display.h"
#include "Simulation.h"

// ���������� ������������ ���� ����������� ����������
using namespace std;
using namespace glm;

int main(int argv, char** argc)
{
    setlocale(LC_ALL, "ru");

    // ������������� ���������� GLUT
    glutInit(&argv, argc);
    // ������������� ������� (������ ������)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    // �������� ����:
    // 1. ������������� ������� ����� ���� ����
    glutInitWindowPosition(200, 200);
    // 2. ������������� ������ ����
    glutInitWindowSize(800, 600);
    // 3. ������� ����
    glutCreateWindow("Lab_04");

    // �������� ����� ������� ���������
    glEnable(GL_LIGHTING);
    // �������� ������� �������� �����
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // ��������� ������� ��������� ������
    // ������������� �������, ������� ����� ���������� ��� ����������� ����
    glutDisplayFunc(display);
    // ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
    glutReshapeFunc(reshape);
    // ������������� �������, ������� ����� ���������� ���������
    glutIdleFunc(simulation);

    initData();

    // �������� ���� ��������� ��������� ��
    glutMainLoop();

    return 0;
};