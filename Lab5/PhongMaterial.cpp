#include "PhongMaterial.h"

std::string DIFFUSE_TEXT = "diffuse:";
std::string AMBIENT_TEXT = "ambient:";
std::string SPECULAR_TEXT = "specular:";
std::string EMISSION_TEXT = "emission:";
std::string SHINESS_TEXT = "shininess:";

PhongMaterial::PhongMaterial()
    : ambient()
    , diffuse()
    , specular()
    , emission()
    , shininess()
{
}

void PhongMaterial::setAmbient(vec4 color)
{
    ambient = color;
}

void PhongMaterial::setDiffuse(vec4 color)
{
    diffuse = color;
}

void PhongMaterial::setSpecular(vec4 color)
{
    specular = color;
}

void PhongMaterial::setEmission(vec4 color)
{
    emission = color;
}

void PhongMaterial::setShininess(float p)
{
    shininess = p;
}

void PhongMaterial::load(string filename)
{
    ifstream file(filename);
    string parameterName;
    float r, g, b, a;

    file >> parameterName;
    while (file) {
        if (parameterName == DIFFUSE_TEXT) {
            file >> r >> g >> b >> a;
            setDiffuse(vec4(r, g, b, a));
        } else if (parameterName == AMBIENT_TEXT) {
            file >> r >> g >> b >> a;
            setAmbient(vec4(r, g, b, a));
        } else if (parameterName == SPECULAR_TEXT) {
            file >> r >> g >> b >> a;
            setSpecular(vec4(r, g, b, a));
        } else if (parameterName == EMISSION_TEXT) {
            file >> r >> g >> b >> a;
            setEmission(vec4(r, g, b, a));
        } else if (parameterName == SHINESS_TEXT) {
            file >> a;
            setShininess(a);
        }
        file >> parameterName;
    }

    file.close();
}

void PhongMaterial::apply()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
    glMaterialfv(GL_FRONT, GL_EMISSION, &emission[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
