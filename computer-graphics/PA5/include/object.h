#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include "graphics_headers.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

class Object
{
  public:
    Object(std::string filename);
    ~Object();
    void Update(unsigned int dt, glm::mat4 origin);
    void Render();

    void StopStartAll();          //
    void StopStartOrbit();        //
    void StopStartRotation();     //
    void ReverseAll();            //
    void ReverseOrbit();          //
    void ReverseRoatation();      //
    void IncreaseOrbitSpeed();    //  Controls that may or may not eventually be used
    void IncreaseRotationSpeed(); //
    void DecreaseOrbitSpeed();    //
    void DecreaseRoationSpeed();  //
    void IncreaseOrbitWidth();    //
    void IncreaseOrbitLength();   //
    void DecreaseOrbitWidth();    //
    void DecreaseOrbitLength();   //
    void IncreaseSize();          //
    void DecreaseSize();          //
    void ResetAll();              //

    //This will set our planet attributes like orbit, size, speed, etc. More attributes may need to be added later
    void SetValues(float o_vel, float r_vel, float o_width, float o_length, float new_scale, float new_tip);

    //returns the model matrix
    glm::mat4 GetModel();

    //Matrix magic. Returns the objects model location alone without information concerning
    //which way it is facing. This is used when translating moons around planets. They should
    //be translating WRT the planet's GetLocation()
    glm::mat4 GetLocation();

  private:
    glm::mat4 model;

    const aiScene* m_scene;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbit_angle, rotate_angle, orbit_vel, rotate_vel, scale, orbit_width, orbit_length, tip;
    float og_orbit_vel, og_rotate_vel, og_scale, og_orbit_width, og_orbit_length, og_tip;
    bool moving_orbit, moving_rotate, rev_orbit, rev_rotate;

};

#endif /* OBJECT_H */
