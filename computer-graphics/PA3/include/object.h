#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, char key, bool new_event, glm::mat4 origin);
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    glm::mat4 parent_model;


    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle, orbit_angle, rotate_angle;
    bool moving_orbit, moving_rotate, rev_orbit, rev_rotate;
};

#endif /* OBJECT_H */
