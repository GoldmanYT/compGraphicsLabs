#include "Mesh.h"

string COORD_TEXT = "v";
string NORMAL_TEXT = "vn";
string TEX_COORD_TEXT = "vt";
string FACE_TEXT = "f";

Mesh::Mesh()
{
}

void Mesh::load(string filename)
{
    // вектор для хранения геометрических координат
    vector<vec3> v;
    // вектор для хранения нормалей
    vector<vec3> n;
    // вектор для хранения текстурных координат
    vector<vec2> t;
    // вектор для хранения индексов атрибутов, для построения вершин
    vector<ivec3> fPoints;
    // входной obj-файл
    ifstream file(filename);
    // имя вводимого параметра
    string parameterName;
    // строка для временных данных
    string temp;

    if (!file.is_open()) {
        return;
    }

    while (file) {
        float x, y, z;
        file >> parameterName;
        if (parameterName == COORD_TEXT) {
            file >> x >> y >> z;
            v.push_back(vec3 { x, y, z });
        } else if (parameterName == NORMAL_TEXT) {
            file >> x >> y >> z;
            n.push_back(vec3 { x, y, z });
        } else if (parameterName == TEX_COORD_TEXT) {
            file >> x >> y >> z;
            t.push_back(vec2 { x, y });
        } else if (parameterName == FACE_TEXT) {
            for (int i = 0; i < 3; ++i) {
                getline(file, temp, '/');
                x = stof(temp);
                getline(file, temp, '/');
                y = stof(temp);
                file >> z;
                fPoints.push_back(ivec3 { x - 1, z - 1, y - 1 });
            }
        } else {
            getline(file, temp);
        }
    }
    for (size_t i = 0; i < fPoints.size(); ++i) {
        ivec3 indexes = fPoints[i];
        vertices.push_back(
            { v[indexes[0]],
                n[indexes[1]],
                t[indexes[2]] });
    }
}

void Mesh::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices.data()->coord);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), vertices.data()->normal);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), vertices.data()->texCoord);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
