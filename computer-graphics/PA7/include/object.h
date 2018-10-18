#ifndef OBJECT_H
#define OBJECT_H

#include "mesh.h"



class Object
{
  public:
    Object(std::string filename);
    ~Object();
    void Update(unsigned int dt, glm::mat4 origin);
    void Render();
    void InitMesh();
    std::vector<GLuint> loadMaterialTextures(aiMaterial *mat, aiTextureType type);

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
    void UseScaled();

    //This will set our planet attributes like orbit, size, speed, etc. More attributes may need to be added later
    void SetValues(float o_vel, float r_vel, float o_width, float o_length, float new_scale, float new_tip, float new_x_axis, float new_y_axis, float new_z_axis, double new_start_angle, bool backwards);
    void SetScaledValues(float s_scale, float s_width, float s_length, float s_x, float s_y, float s_z, float s_tip);

    //returns the model matrix
    glm::mat4 GetModel();

    //Matrix magic. Returns the objects model location alone without information concerning
    //which way it is facing. This is used when translating moons around planets. They should
    //be translating WRT the planet's GetLocation()
    glm::mat4 GetLocation();
    glm::vec3 GetLocationVector();
    void UseActual();
    void initOrbitLine();
    void RenderOrbit();

  private:
    glm::mat4 model;

    const aiScene* m_scene;

    std::string m_textDirectory;
    std::string m_objDirectory;

    std::vector<Mesh> meshes;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    float rotate_angle, orbit_vel, rotate_vel, scale, orbit_width, orbit_length, tip, x_axis, y_axis, z_axis;
    float og_orbit_vel, og_rotate_vel, og_scale, og_orbit_width, og_orbit_length, og_tip;
    bool moving_orbit, moving_rotate, rev_orbit, rev_rotate;
    float scaled_scale, scaled_width, scaled_length;
    double orbit_angle;
    float x, y, z;
    float scale_x, scale_y, scale_z, scale_tip;

    GLuint OVBO, OVAO;
    std::vector<glm::vec3> orbit_vertices;
};

#endif /* OBJECT_H */
