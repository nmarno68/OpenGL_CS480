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

    Object *m_ground;
    Object *m_skybox;
    Object *m_skyboxSunset;

  float ambientStrength;
  bool phong;
  glm::vec3 ambient_color;
  int skybox_used;
  bool normals;

  private:

    std::string ErrorString(GLenum error);

    Shader *m_phong;
    Shader *m_gourand;
    Shader *m_texture;




    //phong
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    GLint m_viewPos;
    GLint m_specular_brightness;
    GLint m_specular_size;
    GLint m_ambientStrength;
    GLint m_ambient_color;



    //gourand
    GLint m_gprojectionMatrix;
    GLint m_gviewMatrix;
    GLint m_gmodelMatrix;

    GLint m_gviewPos;
    GLint m_gspecular_brightness;
    GLint m_gspecular_size;
    GLint m_gambientStrength;
    GLint m_gambient_color;


    //texture
    GLint m_tprojectionMatrix;
    GLint m_tviewMatrix;
    GLint m_tmodelMatrix;




    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;

};

#endif /* GRAPHICS_H */
