#ifndef OBJECT_H
#define OBJECT_H

#include "mesh.h"



class Object
{
  public:
    Object(std::string filename, int shape, bool needsLoading, float s_x, float s_y, float s_z);
    ~Object();
    void Update(unsigned int dt, glm::mat4 origin, float scale);
    void Render();
    void InitMesh();
    std::vector<GLuint> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    void SetValues(float specB, int specS );

    //returns the model matrix
    glm::mat4 GetModel();

    btRigidBody* GetRigidBody();

        //Matrix magic. Returns the objects model location alone without information concerning
    //which way it is facing. This is used when translating moons around planets. They should
    //be translating WRT the planet's GetLocation()
    glm::mat4 GetLocation();
    glm::vec3 GetLocationVector();

    void SetBullet(int m, glm::vec3 inert, bool kinObject, bool phys, glm::vec3 start);

    bool m_physics;
    int m_shape;
    float specular_brightness;
    int specular_size;
    bool t_mesh;

    btRigidBody* m_rigidBody;

  private:
    glm::mat4 model;

    const aiScene* m_scene;

    //Bullet vertex stuff
    bool triangle_Shape;
    btCollisionShape* m_collisionShape;
    btTriangleMesh* m_btTriangleObject;


    //Bullet object characteristics?
    btDefaultMotionState* m_shapeMotionState;



    std::string m_textDirectory;
    std::string m_objDirectory;

    std::vector<Mesh> meshes;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    glm::vec3 initial_translate;

    float scale_x, scale_y, scale_z;
};

#endif /* OBJECT_H */
