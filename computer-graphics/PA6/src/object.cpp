#include "object.h"

Object::Object(std::string filename, std::string textname) //each time we initialize a planet we give a different
{                                     //file name for the object (because each has a different texture)
                                      //however, every planet will be the same size when we load them because
                                      //scaling in the code is more precise than creating them at a certain size in blender

 //File Path to find object name
  std::string filepath = "../src/objects/";
  std::string textpath(filepath);

 //append the given filename

  filepath.append(filename);
  textpath.append(textname);


 //Assimp object loading

 //Create our importer which reads the file for us, thank god
  Assimp::Importer importer;


  //Reading the file in one line, bless
  m_scene = importer.ReadFile(filepath, aiProcess_Triangulate);

  //Extracting the mesh from the scene
  const aiMesh* mesh = m_scene->mMeshes[0]; //for our purposes, we just have the one mesh

  //This is the same process of constructing the vertices and indices that we did when we
  //were writing our own object loader
  InitMesh(mesh);

  Magick::Blob my_blob;
  Magick::Image image;
  unsigned int* data;

  try {
    //std::cout << textpath << std::endl;
    image.read(textpath);
    //std::cout << "2" << std::endl;
    image.write(&my_blob, "RGBA");
    //std::cout << "3" << std::endl;
  }

  catch (Magick::Error& Error) {
    std::cout << "Error loading texture '" << textpath << "': " << Error.what() << std::endl;
  }


  //Pointing our GLuint pointer to a place in the gpu
  glGenTextures(1, &m_textureObj);

  //Specifies the type of texture the pointer is pointing at (still nothing actually there)
  glBindTexture(GL_TEXTURE_2D, m_textureObj);

  //Reading our texture data into the place we set up in memory
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, my_blob.data());

  //"fits" the texture to our object in the way we want it to
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  //Releasing out texture into the wild because we did all the things
  //We can access the texture with m_textureObj in the gpu so we dont need it no mo.
  glBindTexture(GL_TEXTURE_2D, 0);


  orbit_angle = 0.0f;
  rotate_angle = 0.0f;

  //control variables

  //original
  og_orbit_vel = 1;   //
  og_rotate_vel = 1;  //
  og_orbit_width = 1; // Different for each planet. Can be set in the
  og_orbit_length = 1;// SetValues function when each planet is created.
  og_scale = 1;       //
  og_tip = 1;         //

  //Ones that can be modified or reset to originals
  orbit_vel = og_orbit_vel;
  rotate_vel = og_rotate_vel;
  orbit_width = og_orbit_width;
  orbit_length = og_orbit_length;
  scale = og_scale;
  tip = og_tip;//*** still needs work

  //Orbit and rotation flags
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

void Object::Update(unsigned int dt, glm::mat4 origin)
{

  //Axis of rotation - determined by tilt
  //model = glm::rotate(model, (float) (23.5), glm::vec3(0.0, 0.0, 1.0));


  if(moving_orbit)
  {
    if(rev_orbit)
    {
      orbit_angle -= (dt * M_PI / 1000) * orbit_vel;
    }
    else
    {
      orbit_angle += (dt * M_PI / 1000) * orbit_vel;
    }
  }
  model = glm::translate(origin, glm::vec3(sin(orbit_angle) * orbit_width, -sin(orbit_angle) * tip, cos(orbit_angle) * orbit_length));


  if(moving_rotate)
  {
    if(rev_rotate)
    {
      rotate_angle -= (dt * M_PI / 1000) * rotate_vel;
    }
    else
    {
      rotate_angle += (dt * M_PI / 1000) * rotate_vel;
    }
  }
  model = glm::rotate(model, (rotate_angle), glm::vec3(0.0, 1.0, 0.0)); //This axis needs to be dependent on tilt

  model = glm::scale(model, glm::vec3(scale, scale, scale));

}

glm::mat4 Object::GetModel()
{
  return model;
}

glm::mat4 Object::GetLocation()
{
  return glm::translate(glm::mat4(1.0f), glm::vec3(model[3]));
}

void Object::Render()
{

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  //Basically saying that we're using a texture
  glActiveTexture(GL_TEXTURE0);

  //Binding the object's texture that we initialized
  glBindTexture(GL_TEXTURE_2D, m_textureObj);


  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  //Unbind the texture when we're done drawing
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Object::InitMesh(const aiMesh* mesh)
{

  //This is the same process of constructing the vertices and indices that we did when we
  //were writing our own object loader
  const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);


  for(int i = 0; i < mesh->mNumVertices; i++)
  {
    const aiVector3D* pPos = &(mesh->mVertices[i]);
    const aiVector3D* pNormal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
    const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

    Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
             glm::vec2(pTexCoord->x, -pTexCoord->y),
             glm::vec3(pNormal->x, pNormal->y, pNormal->z));

    Vertices.push_back(v);
  }

  for (unsigned int i = 0 ; i < mesh->mNumFaces ; i++)
  {
    const aiFace& Face = mesh->mFaces[i];
    assert(Face.mNumIndices == 3);
    Indices.push_back(Face.mIndices[0]);
    Indices.push_back(Face.mIndices[1]);
    Indices.push_back(Face.mIndices[2]);
  }

}

void Object::StopStartAll()
{
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
}

void Object::StopStartOrbit()
{
  moving_orbit = !moving_orbit;
}

void Object::StopStartRotation()
{
  moving_rotate = !moving_rotate;
}

void Object::ReverseAll()
{
  rev_orbit = !rev_orbit;
  rev_rotate = !rev_rotate;
}

void Object::ReverseOrbit()
{
  rev_orbit = !rev_orbit;
}

void Object::ReverseRoatation()
{
  rev_rotate = !rev_rotate;
}

void Object::IncreaseOrbitSpeed()
{
  orbit_vel += .05;
}

void Object::IncreaseRotationSpeed()
{
  rotate_vel += .05;
}

void Object::DecreaseOrbitSpeed()
{
  if(orbit_vel > 0)
  {
    orbit_vel -= .05;
  }
}

void Object::DecreaseRoationSpeed()
{
  if(rotate_vel > 0)
  {
    rotate_vel -= .05;
  }
}

void Object::IncreaseOrbitWidth()
{
  orbit_width += .05;
}

void Object::IncreaseOrbitLength()
{
  orbit_length += .05;
}

void Object::DecreaseOrbitWidth()
{
  if(orbit_width > 0)
  {
    orbit_width -= .05;
  }
}

void Object::DecreaseOrbitLength()
{
  if(orbit_length > 0)
  {
    orbit_length -= .05;
  }
}

void Object::IncreaseSize()
{
  scale += .02;
}

void Object::DecreaseSize()
{
  if(scale > .02)
  {
    scale -= .02;
  }
}

void Object::ResetAll()
{
  orbit_vel = og_orbit_vel;
  rotate_vel = og_rotate_vel;
  orbit_width = og_orbit_width;
  orbit_length = og_orbit_length;
  scale = og_scale;
  tip = og_tip;
}

void Object::SetValues(float o_vel, float r_vel, float o_width, float o_length, float new_scale, float new_tip)
{
  og_orbit_vel = o_vel;
  og_rotate_vel = r_vel;
  og_orbit_width = o_width;
  og_orbit_length = o_length;
  og_scale = new_scale;
  og_tip = new_tip;

  orbit_vel = og_orbit_vel;
  rotate_vel = og_rotate_vel;
  orbit_width = og_orbit_width;
  orbit_length = og_orbit_length;
  scale = og_scale;
  tip = og_tip;

}












