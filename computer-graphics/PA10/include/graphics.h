#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    Camera *m_camera;
    bool scaled_view;
    bool top_view;

    Object* m_boardy;
    Object* m_cyl;
    Object* m_ball;
    Object* m_cube;
	Object* m_leftWall;
	Object* m_rightWall;
	Object* m_topWall;
	Object* m_bottomWall;

  float ambientStrength, spotlight_brightness, spotlight_size;
  bool spot, hard_edge, phong;
  glm::vec3 ambient_color;

  private:

    std::string ErrorString(GLenum error);

    Shader *m_phong;
    Shader *m_gourand;

    //lighting variables
    lightSource* b_1;


    //phong
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    GLint m_viewPos;
    GLint m_ballPos;
    GLint m_spotlight_size;
    GLint m_spotlight_brightness;
    GLint m_specular_brightness;
    GLint m_specular_size;
    GLint m_ambientStrength;
    GLint m_hard_edge;
    GLint m_ambient_color;

    GLint m_bumper1;
    GLint m_bumper1_c;


    //gourand
    GLint m_gprojectionMatrix;
    GLint m_gviewMatrix;
    GLint m_gmodelMatrix;

    GLint m_gviewPos;
    GLint m_gballPos;
    GLint m_gspotlight_size;
    GLint m_gspotlight_brightness;
    GLint m_gspecular_brightness;
    GLint m_gspecular_size;
    GLint m_gambientStrength;
    GLint m_ghard_edge;
    GLint m_gambient_color;

    GLint m_gbumper1;
    GLint m_gbumper1_c;


    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;

};

#endif /* GRAPHICS_H */
