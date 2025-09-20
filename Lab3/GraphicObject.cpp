#include "GraphicObject.h"

GraphicObject::GraphicObject()
    : position()
    , angle(0)
    , color()
{
}

void GraphicObject::setPosition(vec3 position)
{
    this->position = position;
    recalculateModelMatrix();
}

vec3 GraphicObject::getPosition()
{
    return position;
}

void GraphicObject::setAngle(float angle)
{
    this->angle = radians(angle);
    recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
    return angle;
}

void GraphicObject::setСolor(vec3 color)
{
    this->color = color;
}

vec3 GraphicObject::getColor()
{
    return color;
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
    modelMatrix = mat4(1);
    modelMatrix = translate(modelMatrix, position);
    modelMatrix = rotate(modelMatrix, angle, vec3(0, 1, 0));
    modelMatrix = scale(modelMatrix, vec3(1, 1, 1));
}

// вывести объект
void GraphicObject::draw()
{
    glColor3f(color.r, color.g, color.b);
    glPushMatrix();
    glMultMatrixf(&modelMatrix[0][0]);
    glutWireTeapot(1.0);
    glPopMatrix();
}