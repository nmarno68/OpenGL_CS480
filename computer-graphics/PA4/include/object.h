#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"


class Object
{
  public:
    Object(int argc, char** argv);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    bool LoadOBJ(std::string filepath, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices);

    glm::mat4 GetModel();

    bool m_initialize = true;

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<glm::vec3> Vertices_p;
    GLuint VB;
    GLuint IB;


    float angle;
};

#endif /* OBJECT_H */
