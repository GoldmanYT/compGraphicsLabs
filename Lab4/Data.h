#pragma once

#include "Camera.h"
#include "GraphicObject.h"

#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include <vector>
#include <string>
#include <windows.h>

extern const float VERTICAL_SPEED;

extern const float HORIZONTAL_SPEED;

extern const float ZOOM_SPEED;
// ������� �������� ������������������
extern float FREQUENCY;
// ���������� ����� � ����� �� ���������� �����
extern long long prevTime;
// ����� ������ � �������
extern long long FPS;
// ����� ��������� � ��������
extern float simulationTime;
// ����� ��� ����� ����
extern char windowTitle[256];

// ������ ����������� ��������
extern std::vector<GraphicObject> graphicObjects;
// ������������ ������
extern Camera camera;
// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData();
