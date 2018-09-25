#include "object.h"
#include <fstream>
#include <iostream>

Object::Object(int argc, char** argv)
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



  /* Vertices = {
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
   */


  srand(25649);

  std::string filepath = "../src/objects/";
  if(argc > 1)
  {
    filepath.append(argv[1]);
    m_initialize = LoadOBJ(filepath, &Vertices, &Indices);
  }
  else
    m_initialize = false;

  //now we have all the stuff and things
  /*
  for(int i = 0; i < Vertices_p.size(); i++)
  {
    Vertex* temp = new Vertex(Vertices_p[i], glm::vec3( (float)((rand()*1000)%255) , (float)((rand()*1000)%255), (float)((rand()*1000)%255)));
    Vertices.push_back(*temp);
  }
  */

  angle = 0.0f;

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

void Object::Update(unsigned int dt)
{

  angle += dt * M_PI/1000;
  model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
  model = glm::rotate(model, (angle)/4, glm::vec3(1.0, 0.0, 0.0));


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

bool Object::LoadOBJ(std::string filepath, std::vector<Vertex>* vertices , std::vector<unsigned int>* indices)
{
  std::ifstream obj_file;

  int count = 0;
  int ran1 = rand();
  int ran2 = rand();
  int ran3 = rand();

  obj_file.open(filepath);
  if(!obj_file.is_open())
  {
    m_initialize = false;
  }

  std::string lineHeader;
  obj_file >> lineHeader;

  while(obj_file.good())
  {
    count++;
    if (lineHeader == "v")
    {
      glm::vec3 position;
      glm::vec3 color;
      obj_file >> position.x;
      obj_file >> position.y;
      obj_file >> position.z;

      if(count < 30)
      {
        Vertex* newVert = new Vertex(position, glm::vec3( (float)(rand()%1000)/1000, (float)(rand()%1000)/1000, (float)(rand()%1000)/1000));
        vertices->push_back(*newVert);

      }
      else
      {
        if(count % 25000 == 0)
        {
          ran1 = rand();
          ran2 = rand();
          ran3 = rand();
        }
        Vertex* newVert = new Vertex(position, glm::vec3( (float)(ran1%1000)/1000, (float)(ran2%1000)/1000, (float)(ran3%1000)/1000));
        vertices->push_back(*newVert);
      }

    }
    else if ( lineHeader == "f" )
    {
      for(int i = 0; i < 3; i++)
      {
        unsigned int val;
        std::string temp;

        obj_file >> val;
        if(obj_file.peek() == '/')
        {
          obj_file >> temp;
        }

        indices->push_back(val - 1);
      }
    }

    else
    {
      getline(obj_file, lineHeader);
    }
    obj_file >> lineHeader;
  }

  obj_file.close();

  return true;
}