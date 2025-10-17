#include "Light.h"

Light::Light()
{
    setPosition(vec3(1));
    setAmbient(vec4(1));
    setDiffuse(vec4(1));
    setSpecular(vec4(1));
}

Light::Light(vec3 position)
{
    setPosition(position);
    setAmbient(vec4(1));
    setDiffuse(vec4(1));
    setSpecular(vec4(1));
}

Light::Light(float x, float y, float z)
{
    setPosition(vec3(x, y, z));
    setAmbient(vec4(1));
    setDiffuse(vec4(1));
    setSpecular(vec4(1));
}

void Light::setPosition(vec3 position)
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    this->position.w = 1;
}

void Light::setAmbient(vec4 color)
{
    ambient = color;
}

void Light::setDiffuse(vec4 color)
{
    diffuse = color;
}

void Light::setSpecular(vec4 color)
{
    specular = color;
}

void Light::apply(GLenum LightNumber)
{
    glLightfv(LightNumber, GL_AMBIENT, &ambient[0]);
    glLightfv(LightNumber, GL_DIFFUSE, &diffuse[0]);
    glLightfv(LightNumber, GL_SPECULAR, &specular[0]);
    glLightfv(LightNumber, GL_POSITION, &position[0]);
}
