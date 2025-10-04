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
// �������� �����
Light light;

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
    shared_ptr<PhongMaterial> material1 = shared_ptr<PhongMaterial>(new PhongMaterial);
    material1->load("data/materials/material_1.txt");
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180);
    tempGraphicObject.setMaterial(material1);
    graphicObjects.push_back(tempGraphicObject);

    // 2 -----------------------------------------
    shared_ptr<PhongMaterial> material2 = shared_ptr<PhongMaterial>(new PhongMaterial);
    material2->load("data/materials/material_2.txt");
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270);
    tempGraphicObject.setMaterial(material2);
    graphicObjects.push_back(tempGraphicObject);

    // 3 -----------------------------------------
    shared_ptr<PhongMaterial> material3 = shared_ptr<PhongMaterial>(new PhongMaterial);
    material3->load("data/materials/material_3.txt");
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0);
    tempGraphicObject.setMaterial(material3);
    graphicObjects.push_back(tempGraphicObject);

    // 4 -----------------------------------------
    shared_ptr<PhongMaterial> material4 = shared_ptr<PhongMaterial>(new PhongMaterial);
    material4->load("data/materials/material_4.txt");
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90);
    tempGraphicObject.setMaterial(material4);
    graphicObjects.push_back(tempGraphicObject);
}