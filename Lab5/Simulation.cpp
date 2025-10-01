#include "Simulation.h"

using namespace std;

void updateSimulationTime()
{
    LARGE_INTEGER tempInt;
    long long currentTime;

    QueryPerformanceCounter(&tempInt);
    currentTime = tempInt.QuadPart;

    simulationTime = (currentTime - prevTime) / FREQUENCY;
    prevTime = currentTime;
    FPS = 1 / simulationTime;
}

float getSimulationTime()
{
    return simulationTime;
}

void simulation()
{
    updateSimulationTime();
    // определение времени симуляции
    float simulationTime = getSimulationTime();
    // устанавливаем признак того, что окно нуждается в перерисовке
    glutPostRedisplay();
    camera.apply();

    keyboardFunc();
};

// Функция обработки нажатия клавиш
void keyboardFunc()
{
    // определение времени симуляции
    float simulationTime = getSimulationTime();
    if (GetAsyncKeyState(VK_UP)) {
        camera.rotateUpDown(VERTICAL_SPEED * simulationTime);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        camera.rotateUpDown(-VERTICAL_SPEED * simulationTime);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        camera.rotateLeftRight(HORIZONTAL_SPEED * simulationTime);
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        camera.rotateLeftRight(-HORIZONTAL_SPEED * simulationTime);
    }
    if (GetAsyncKeyState(VK_OEM_PLUS) || GetAsyncKeyState(VK_ADD)) {
        camera.zoomInOut(ZOOM_SPEED * simulationTime);
    }
    if (GetAsyncKeyState(VK_OEM_MINUS) || GetAsyncKeyState(VK_SUBTRACT)) {
        camera.zoomInOut(-ZOOM_SPEED * simulationTime);
    }
}
