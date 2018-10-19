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
    void IncSimSpeed();
    void DecSimSpeed();
    void resetAll();
    void scaledView();
    void actualView();

    //I thought it would be nicer if we could call them by name
    //instead of having numbers in an array
    Object *m_milkyway;
    Object *m_Sun;

    Object *m_mercury;

    Object *m_venus;

    Object *m_earth;
    Object *m_moon;

    Object *m_mars;
    Object *m_deimos;
    Object *m_phobos;

    Object *m_jupiter;
    Object *m_ganymede;
    Object *m_callisto;
    Object *m_io;
    Object *m_europa;

    Object *m_saturn;
    Object *m_titan;
    Object *m_enceladus;

    Object *m_uranus;
    Object *m_titania;
    Object *m_oberon;
    Object *m_umbriel;
    Object *m_ariel;
    Object *m_miranda;

    Object *m_neptune;
    Object *m_triton;

    Object *m_pluto;
    Object *m_charon;
    Object *m_secret;

    Camera *m_camera;
    int target_planet;
    bool planet_view;
    bool scaled_view;
    bool top_view;
    bool light;

  private:
    std::string ErrorString(GLenum error);

    Shader *m_shader;
    Shader *m_orbit_shader;
    Shader *m_light_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    GLint m_orbitModel;
    GLint m_orbitView;
    GLint m_orbitProjection;

    GLint m_sunModel;
    GLint m_sunView;
    GLint m_sunProjection;

    GLint m_viewPos;


};

#endif /* GRAPHICS_H */
