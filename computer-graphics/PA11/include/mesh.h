#include <vector>
#include <string>
#include "graphics_headers.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>


class Mesh{

  public:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<GLuint> Textures;
    std::vector<GLuint> Normals;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<GLuint> textures, std::vector<GLuint> normals);

    void Draw();

  private:
    GLuint VAO, VBO, EBO;

    void setUp(); //binds and initializes VAO VBO and EBO
};