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
// частота счЄтчика производительности
extern float FREQUENCY;
// предыдущее врем€ в тиках до обновлени€ кадра
extern long long prevTime;
// число кадров в секунду
extern long long FPS;
// врем€ симул€ции в секундах
extern float simulationTime;
// буфер дл€ имени окна
extern char windowTitle[256];

// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используема€ камера
extern Camera camera;
// функци€ дл€ инициализации всех общих данных (камера, объекты и т.д.)
void initData();
