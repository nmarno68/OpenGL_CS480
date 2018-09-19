#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, glm::mat4 origin);
    void Render();

    void StopStartAll();
    void StopStartOrbit();
    void StopStartRotation();
    void ReverseAll();
    void ReverseOrbit();
    void ReverseRoatation();
    void IncreaseOrbitSpeed();
    void IncreaseRotationSpeed();
    void DecreaseOrbitSpeed();
    void DecreaseRoationSpeed();
    void IncreaseOrbitWidth();
    void IncreaseOrbitLength();
    void DecreaseOrbitWidth();
    void DecreaseOrbitLength();
    void IncreaseSize();
    void DecreaseSize();
    void ResetAll();

    void SetValues(float o_vel, float r_vel, float o_width, float o_length, float new_scale, float new_tip);

    glm::mat4 GetModel();
    glm::mat4 GetLocation();

  private:
    glm::mat4 model;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbit_angle, rotate_angle, orbit_vel, rotate_vel, scale, orbit_width, orbit_length, tip;
    float og_orbit_vel, og_rotate_vel, og_scale, og_orbit_width, og_orbit_length, og_tip;
    bool moving_orbit, moving_rotate, rev_orbit, rev_rotate;
};

#endif /* OBJECT_H */
