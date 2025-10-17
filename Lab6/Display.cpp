#include "Display.h"

using namespace std;

long long getFPS()
{
    // для получения корректного числа кадров в секунду
    // необходимо вызвать функцию getSimulationTime()
    return FPS;
}

// CALLBACK-ФУНКЦИЯ ВЫЗЫВАЕТСЯ ПРИ ПЕРЕРИСОВКЕ ОКНА
void display()
{
    // отчищаем буфер цвета и буфер глубины
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    // включаем режим расчета освещения
    glEnable(GL_LIGHTING);
    // устанавливаем камеру
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.apply();
    // устанавливаем источник света
    light.apply(GL_LIGHT0);
    // выводим все графические объекты
    for (auto& go : graphicObjects) {
        go.draw();
    }
    // смена переднего и заднего буферов
    glutSwapBuffers();
    // выводим заголовок окна
    sprintf_s(windowTitle, 128, "Lab 5 [%lld FPS]", getFPS());
    glutSetWindowTitle(windowTitle);
};

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
    // установить новую область просмотра, равную всей области окна
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // установить матрицу проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};
