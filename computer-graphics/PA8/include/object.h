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

    //returns the model matrix
    glm::mat4 GetModel();

    //Matrix magic. Returns the objects model location alone without information concerning
    //which way it is facing. This is used when translating moons around planets. They should
    //be translating WRT the planet's GetLocation()
    glm::mat4 GetLocation();
    glm::vec3 GetLocationVector();

  private:
    glm::mat4 model;

    const aiScene* m_scene;

    std::string m_textDirectory;
    std::string m_objDirectory;

    std::vector<Mesh> meshes;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

};

#endif /* OBJECT_H */
