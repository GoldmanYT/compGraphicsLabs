#include <windows.h>

#include <iostream>

#include "GL/freeglut.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include <vector>

#include "Camera.h"
#include "GraphicObject.h"

// ���������� ������������ ���� ����������� ����������
using namespace std;
using namespace glm;

vector<GraphicObject> graphicObjects;
Camera camera;

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
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �������� ���� �������
    glEnable(GL_DEPTH_TEST);

    // ������������� ������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.apply();

    for (auto& go : graphicObjects) {
        go.draw();
        // glutWireTeapot(1.0);
    }

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
    camera.apply();
};

// ������� ��������� ������� ������
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
    glutCreateWindow("Laba_04");

    // ��������� ������� ��������� ������
    // ������������� �������, ������� ����� ���������� ��� ����������� ����
    glutDisplayFunc(display);
    // ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
    glutReshapeFunc(reshape);
    // ������������� �������, ������� ����� ������� ����� 20 ��
    glutTimerFunc(20, simulation, 0);
    // ������������� �������, ������� ����� ���������� ��� ������� �� �������
    glutKeyboardFunc(keyboardFunc);

    GraphicObject tempGraphicObject;
    // ������������� ����������� ��������
    // 1 -----------------------------------------
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180);
    tempGraphicObject.set�olor(vec3(1, 0, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 2 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270);
    tempGraphicObject.set�olor(vec3(0, 1, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 3 -----------------------------------------
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0);
    tempGraphicObject.set�olor(vec3(0, 0, 1));
    graphicObjects.push_back(tempGraphicObject);
    // 4 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90);
    tempGraphicObject.set�olor(vec3(1, 1, 1));
    graphicObjects.push_back(tempGraphicObject);

    camera.setPosition(vec3(10, 15, 17.5));

    // �������� ���� ��������� ��������� ��
    glutMainLoop();

    return 0;
};