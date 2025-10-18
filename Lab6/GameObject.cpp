#include "GameObject.h"

GameObject::GameObject()
    : position()
{
}

void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
    this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
    position = { x, y };
}

void GameObject::setPosition(ivec2 position)
{
    this->position = position;
}

ivec2 GameObject::getPosition()
{
    return position;
}

void GameObject::draw()
{
    graphicObject.draw();
}
