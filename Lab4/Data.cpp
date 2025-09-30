#include "Data.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;


const float VERTICAL_SPEED = 90.0f;

const float HORIZONTAL_SPEED = 90.0f;

const float ZOOM_SPEED = 10.0f;

// ������� �������� ������������������
float FREQUENCY;
// ���������� ����� � ����� �� ���������� �����
long long prevTime;
// ����� ������ � �������
long long FPS;
// ����� ��������� � ��������
float simulationTime;
// ����� ��� ����� ����
char windowTitle[256];

// ������ ����������� ��������
vector<GraphicObject> graphicObjects;

// ������������ ������
Camera camera;

// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData()
{
    LARGE_INTEGER tempInt;

    // ������������� �������
    QueryPerformanceFrequency(&tempInt);
    FREQUENCY = tempInt.QuadPart;

    QueryPerformanceCounter(&tempInt);
    prevTime = tempInt.QuadPart;

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
}