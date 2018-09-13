#include "object.h"

Object::Object()
{
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;
  orbit_angle = 0.0f;
  rotate_angle = 0.0f;

  moving_orbit = true;
  moving_rotate = true;
  rev_orbit = false;
  rev_rotate = false;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, char key, bool new_event, glm::mat4 origin)
{
    //if something changed, update object states
    if(new_event)
    {
      switch (key) {
        case 'a':
          if(moving_rotate or moving_orbit)
          {
            moving_rotate = false;
            moving_orbit = false;
          }
          else
          {
            moving_rotate = true;
            moving_orbit = true;
          }
          break;
        case 'f':
          moving_orbit = !moving_orbit;
          break;
        case 'd':
          moving_rotate = !moving_rotate;
          break;
        case 's':
          rev_orbit = !rev_orbit;
          rev_rotate = !rev_rotate;
          break;
        case 'w':
          rev_orbit = !rev_orbit;
          break;
        case 'e':
          rev_rotate = !rev_rotate;
      }
    }
  if(moving_orbit)
  {
    if(rev_orbit)
    {
      orbit_angle -= dt * M_PI / 1000;
      model = glm::translate(origin , glm::vec3(sin(orbit_angle / 2) * 8, -sin(orbit_angle/2) * 2, cos(orbit_angle / 2) * 8));
    }
    else
    {
      orbit_angle += dt * M_PI / 1000;
      model = glm::translate(origin , glm::vec3(sin(orbit_angle / 2) * 8, -sin(orbit_angle/2) * 2, cos(orbit_angle / 2) * 8));
    }
  }
  else
  {
    model = glm::translate(origin , glm::vec3(sin(orbit_angle / 2) * 8, -sin(orbit_angle/2) * 2, cos(orbit_angle / 2) * 8));
  }
  if(moving_rotate)
  {
    if(rev_rotate)
    {
      rotate_angle -= dt * M_PI / 1000;
    }
    else
    {
      rotate_angle += dt * M_PI / 1000;
    }
  }
  model = glm::rotate(model, (rotate_angle) * 2, glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
