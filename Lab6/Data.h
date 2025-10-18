#pragma once

#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"

#include "../glm/glm.hpp"
#include "GL/freeglut.h"

#include <string>
#include <vector>
#include <windows.h>

extern const float VERTICAL_SPEED;
extern const float HORIZONTAL_SPEED;
extern const float ZOOM_SPEED;

extern vector<string> MATERIAL_FILENAMES;

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

// карта проходимости
extern int passabilityMap[21][21];

// список игровых объектов расположенных на карте
// extern std::shared_ptr<GameObject> mapObjects[21][21];

// графический объект дл€ плоскости (частный случай)
extern GraphicObject planeGraphicObject;

// используема€ камера
extern Camera camera;

// источник света
extern Light light;

// используемые материалы
extern vector<shared_ptr<PhongMaterial>> materials;

// используемые меши
extern vector<shared_ptr<Mesh>> meshes;

// функци€ дл€ инициализации всех общих данных (камера, объекты и т.д.)
void initData();
