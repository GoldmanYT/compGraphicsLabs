#include "Display.h"

using namespace std;

long long getFPS()
{
    // ��� ��������� ����������� ����� ������ � �������
    // ���������� ������� ������� getSimulationTime()
    return FPS;
}

// CALLBACK-������� ���������� ��� ����������� ����
void display()
{
    // �������� ����� ����� � ����� �������
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // �������� ���� �������
    glEnable(GL_DEPTH_TEST);
    // �������� ����� ������� ���������
    glEnable(GL_LIGHTING);
    // ������������� ������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.apply();
    // ������������� �������� �����
    light.apply(GL_LIGHT0);
    // ������� ��� ����������� �������
    for (auto& go : graphicObjects) {
        go.draw();
    }
    // ����� ��������� � ������� �������
    glutSwapBuffers();
    // ������� ��������� ����
    sprintf_s(windowTitle, 128, "Lab 5 [%lld FPS]", getFPS());
    glutSetWindowTitle(windowTitle);
};

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
