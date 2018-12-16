#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#define NUM_SPELLS 6
class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    bool Collide(glm::vec3 objLocation1, glm::vec3 objLocation2);

    Camera *m_camera;

    Object *m_ground;
    Object *m_skybox;
    Object *m_skyboxSunset;
    Object *m_grass1;

    Object *m_tree;
    Object *m_rock1;
    Object *m_rock2;
    Object *m_well;

    Object *m_wiz1;
    Object *m_enemy;
    Object *m_enemySprite;

    Object *tester;

    Object *m_spells[NUM_SPELLS];

    vector<Object*> m_fence;

  float ambientStrength;
  bool phong;
  glm::vec3 ambient_color;
  int skybox_used;
  char movement;
  bool normals, moving;
  glm::vec3 l_C, l_D;
  int spellToCast;

  private:

    std::string ErrorString(GLenum error);

    Shader *m_phong;
    Shader *m_gourand;
    Shader *m_texture;
    Shader *m_color;




    //phong
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    GLint m_viewPos;
    GLint m_specular_brightness;
    GLint m_specular_size;
    GLint m_ambientStrength;
    GLint m_ambient_color;

    GLint m_lightDirection;
    GLint m_lightColor;

    GLint m_pointSources;
    GLint m_pointSourceColor;

    GLint m_calcSpellLight;
    GLint m_useNorm;


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


    //Color
    GLint m_cPM, m_cVM, m_cMM;
    GLint m_cColor, m_cCamPos;


    btBroadphaseInterface* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;

    glm::vec3 spell_position[NUM_SPELLS];
    glm::vec3 spell_colors[NUM_SPELLS];
    int spell_casting[NUM_SPELLS];



};

#endif /* GRAPHICS_H */
