#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType, std::string folder);
    void LoadShader(std::string* s, std::string foldername, std::string filename);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
    GLuint GetProgram();

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
