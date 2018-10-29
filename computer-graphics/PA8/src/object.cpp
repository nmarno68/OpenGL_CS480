#include "object.h"

Object::Object(std::string filename) //each time we initialize a planet we give a different
{                                     //file name for the object (because each has a different texture)
                                      //however, every planet will be the same size when we load them because
                                      //scaling in the code is more precise than creating them at a certain size in blender
 //File Path to find object name
  m_objDirectory = "../assets/objects/";
  m_textDirectory = "../assets/textures/";

 //append the given filename

  //sorting out texture files because existence is pain

  m_objDirectory.append(filename);

 //Assimp object loading

 //Create our importer which reads the file for us, thank god
  Assimp::Importer importer;

  //Reading the file in one line, bless
  m_scene = importer.ReadFile(m_objDirectory, aiProcess_Triangulate);

  //This is the same process of constructing the vertices and indices that we did when we
  //were writing our own object loader
  InitMesh();

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

//Update the object's model using all of its unique values
void Object::Update(unsigned int dt, glm::mat4 origin)
{
/*
  model = glm::translate(origin, glm::vec3((sin(orbit_angle) * orbit_width) + x, (-sin(orbit_angle) * tip) + y, (cos(orbit_angle) * orbit_length) + z));

  model = glm::rotate(model, (rotate_angle), glm::vec3(x_axis, y_axis, z_axis)); //This axis needs to be dependent on tilt

  model = glm::scale(model, glm::vec3(scale, scale, scale));
*/
}

glm::mat4 Object::GetModel()
{
  return model;
}

//returns location without direction information as a mat4
glm::mat4 Object::GetLocation()
{
  return glm::translate(glm::mat4(1.0f), glm::vec3(model[3]));
}

//returns location without direction information as a vec3
glm::vec3 Object::GetLocationVector()
{
  return glm::vec3(model[3]);
}

//render all the object's meshes
void Object::Render()
{

  for(int i = 0; i < meshes.size(); i++)
  {
    meshes[i].Draw();
  }
}

void Object::InitMesh()
{

  //This is the same process of constructing the vertices and indices that we did when we
  //were writing our own object loader

  const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

  for(int j = 0; j < m_scene->mNumMeshes; j++)
  {

    std::vector<Vertex> tempVert;
    std::vector<unsigned int> tempInd;
    std::vector<GLuint> temptexture;


    for (int i = 0; i < m_scene->mMeshes[j]->mNumVertices; i++)
    {
      const aiVector3D *pPos = &(m_scene->mMeshes[j]->mVertices[i]);
      const aiVector3D *pNormal = m_scene->mMeshes[j]->HasNormals() ? &(m_scene->mMeshes[j]->mNormals[i]) : &Zero3D;
      const aiVector3D *pTexCoord = m_scene->mMeshes[j]->HasTextureCoords(0) ? &(m_scene->mMeshes[j]->mTextureCoords[0][i]) : &Zero3D;

      Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
               glm::vec2(pTexCoord->x, -pTexCoord->y),
               glm::vec3(pNormal->x, pNormal->y, pNormal->z));

      tempVert.push_back(v);
    }

    for (unsigned int i = 0; i < m_scene->mMeshes[j]->mNumFaces; i++)
    {
      const aiFace &Face = m_scene->mMeshes[j]->mFaces[i];
      assert(Face.mNumIndices == 3);
      tempInd.push_back(Face.mIndices[0]);
      tempInd.push_back(Face.mIndices[1]);
      tempInd.push_back(Face.mIndices[2]);
    }

    //Texture stuff

    temptexture = loadMaterialTextures(m_scene->mMaterials[m_scene->mMeshes[j]->mMaterialIndex], aiTextureType_DIFFUSE);


    Mesh* v = new Mesh(tempVert, tempInd, temptexture);
    meshes.push_back(*v);

  }

}

std::vector<GLuint> Object::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
  std::vector<GLuint> textures;

  //loading in all the diffuse textures, however we only have the capability
  //to render one
  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
  {
    GLuint texture;
    aiString str;
    std::string t_path;
    mat->GetTexture(type, i, &str);

    t_path = m_textDirectory + str.C_Str();

    Magick::Blob my_blob;
    Magick::Image image;
    unsigned int* data;

    try {
      image.read(t_path); //the texture for the mesh we're on
      image.write(&my_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
      std::cout << "Error loading texture '" << t_path << "': " << Error.what() << std::endl;
    }

    //Pointing our GLuint pointer to a place in the gpu
    glGenTextures(1, &texture);

    //Specifies the type of texture the pointer is pointing at (still nothing actually there)
    glBindTexture(GL_TEXTURE_2D, texture);

    //Reading our texture data into the place we set up in memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, my_blob.data());

    //"fits" the texture to our object in the way we want it to
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Releasing out texture into the wild because we did all the things
    //We can access the texture with m_textureObj in the gpu so we dont need it no mo.
    glBindTexture(GL_TEXTURE_2D, 0);

    textures.push_back(texture);
  }
  return textures;
}