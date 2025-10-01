#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

const float VERTICAL_SPEED = 90.0f;
const float HORIZONTAL_SPEED = 90.0f;
const float ZOOM_SPEED = 10.0f;

// частота счётчика производительности
float FREQUENCY;
// предыдущее время в тиках до обновления кадра
long long prevTime;
// число кадров в секунду
long long FPS;
// время симуляции в секундах
float simulationTime;
// буфер для имени окна
char windowTitle[256];

std::string DIFFUSE_TEXT = "diffuse:";
std::string AMBIENT_TEXT = "ambient:";
std::string SPECULAR_TEXT = "specular:";
std::string EMISSION_TEXT = "emission:";
std::string SHINESS_TEXT = "shininess:";

// список графических объектов
vector<GraphicObject> graphicObjects;

// используемая камера
Camera camera;

// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
    LARGE_INTEGER tempInt;

    // инициализация частоты
    QueryPerformanceFrequency(&tempInt);
    FREQUENCY = tempInt.QuadPart;

    QueryPerformanceCounter(&tempInt);
    prevTime = tempInt.QuadPart;

    GraphicObject tempGraphicObject;
    // инициализация графических объектов
    // 1 -----------------------------------------
    tempGraphicObject.setPosition(vec3(5, 0, 0));
    tempGraphicObject.setAngle(180);
    tempGraphicObject.setСolor(vec3(1, 0, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 2 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, -5));
    tempGraphicObject.setAngle(270);
    tempGraphicObject.setСolor(vec3(0, 1, 0));
    graphicObjects.push_back(tempGraphicObject);
    // 3 -----------------------------------------
    tempGraphicObject.setPosition(vec3(-5, 0, 0));
    tempGraphicObject.setAngle(0);
    tempGraphicObject.setСolor(vec3(0, 0, 1));
    graphicObjects.push_back(tempGraphicObject);
    // 4 -----------------------------------------
    tempGraphicObject.setPosition(vec3(0, 0, 5));
    tempGraphicObject.setAngle(90);
    tempGraphicObject.setСolor(vec3(1, 1, 1));
    graphicObjects.push_back(tempGraphicObject);
}