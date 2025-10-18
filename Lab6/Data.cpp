#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

const float VERTICAL_SPEED = 90.0f;
const float HORIZONTAL_SPEED = 90.0f;
const float ZOOM_SPEED = 10.0f;

const int MATERIAL_GREEN = 0;
const int MATERIAL_YELLOW = 1;
const int MATERIAL_GRAY = 2;
const int MATERIAL_DARK_GRAY = 3;

const int MESH_BOX = 0;
const int MESH_CHAMFER_BOX = 1;
const int MESH_SIMPLE_PLANE = 2;
const int MESH_SPHERE = 3;

vector<string> MATERIAL_FILENAMES = {
    "data/materials/material_1.txt",
    "data/materials/material_2.txt",
    "data/materials/material_3.txt",
    "data/materials/material_4.txt"
};

vector<string> MESH_FILENAMES = {
    "data/meshes/Box.obj",
    "data/meshes/ChamferBox.obj",
    "data/meshes/SimplePlane.obj",
    "data/meshes/Sphere.obj"
};

// частота счЄтчика производительности
float FREQUENCY;
// предыдущее врем€ в тиках до обновлени€ кадра
long long prevTime;
// число кадров в секунду
long long FPS;
// врем€ симул€ции в секундах
float simulationTime;
// буфер дл€ имени окна
char windowTitle[256];

// карта проходимости
int passabilityMap[MAP_WIDTH][MAP_HEIGHT] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3,
    3, 0, 2, 1, 2, 0, 2, 0, 2, 2, 2, 1, 2, 0, 2, 0, 2, 0, 2, 2, 3,
    3, 0, 2, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 1, 0, 0, 0, 3,
    3, 0, 1, 0, 2, 2, 1, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 0, 2, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 3,
    3, 0, 2, 2, 1, 1, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 0, 3,
    3, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 2, 2, 2, 0, 2, 0, 2, 2, 1, 2, 2, 2, 1, 2, 2, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3,
    3, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 2, 2, 2, 0, 2, 1, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 3,
    3, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 3,
    3, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 1, 0, 2, 2, 2, 0, 3,
    3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 1, 0, 0, 0, 2, 0, 3,
    3, 0, 2, 0, 2, 1, 2, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 3,
    3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 2, 0, 2, 2, 2, 2, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

// список игровых объектов расположенных на карте
std::shared_ptr<GameObject> mapObjects[MAP_WIDTH][MAP_HEIGHT] {};

// графический объект дл€ плоскости (частный случай)
GraphicObject planeGraphicObject;

// используема€ камера
Camera camera;

// источник света
Light light;

// используемые материалы
vector<shared_ptr<PhongMaterial>> materials;

// используемые меши
vector<shared_ptr<Mesh>> meshes;

// функци€ дл€ инициализации всех общих данных (камера, объекты и т.д.)
void initData()
{
    LARGE_INTEGER tempInt;

    // инициализаци€ частоты
    QueryPerformanceFrequency(&tempInt);
    FREQUENCY = tempInt.QuadPart;

    QueryPerformanceCounter(&tempInt);
    prevTime = tempInt.QuadPart;

    for (auto& filename : MATERIAL_FILENAMES) {
        shared_ptr<PhongMaterial> material = shared_ptr<PhongMaterial>(new PhongMaterial);
        material->load(filename);
        materials.push_back(material);
    }

    for (auto& filename : MESH_FILENAMES) {
        shared_ptr<Mesh> mesh = shared_ptr<Mesh>(new Mesh);
        mesh->load(filename);
        meshes.push_back(mesh);
    }

    GraphicObject tempGraphicObject {};
    tempGraphicObject.setMaterial(materials[3]);
    tempGraphicObject.setMesh(meshes[MESH_SIMPLE_PLANE]);
    planeGraphicObject = tempGraphicObject;

    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            shared_ptr<GameObject> tempGameObject = shared_ptr<GameObject>(new GameObject);
            int gameObjectType = passabilityMap[x][y];
            tempGraphicObject.setMaterial(materials[gameObjectType]);
            tempGraphicObject.setMesh(meshes[gameObjectType]);
            tempGameObject->setPosition(x, y);
            tempGameObject->setGraphicObject(tempGraphicObject);
            mapObjects[x][y] = tempGameObject;
        }
    }
}