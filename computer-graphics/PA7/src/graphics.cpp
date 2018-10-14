#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }


  //create objects
  m_Sun = new Object("sun.obj");
  m_earth = new Object("earth2.obj");
  m_moon = new Object("moon.obj");
  m_saturn = new Object("Saturn.obj");
  m_secret = new Object("moon.obj");



  m_mars = new Object ("moon.obj");
  m_venus = new Object ("moon.obj");
  //m_mercury = new Object ("mercury.obj");
  //m_jupiter = new Object ("jupiter.obj");
  //m_neptune = new Object ("neptune.obj");
  //m_uranus = new Object ("uranus.obj");
  //m_pluto = new Object ("pluto.obj");




  //Set the object values - float o_vel, float r_vel, float o_width, float o_length, float new_scale, tip, x_axis, y_axis, start_angle
  m_Sun->SetValues(0,.05, 0, 0, 2, 0, 0.0, 1.0, 1);
  m_earth->SetValues(.05, .2, 15, 15, 1, 0, 0.0, 1.0, 1);
  m_moon->SetValues(.2, .3, 3, 3, .5, 1, 0.0, 1.0, 1);
  m_saturn->SetValues(0.05, .2, 30, 30, 4, 0, -1.0, 2.5, 1);

  //pluto and charon
  m_secret->SetValues(.05, 0, 50, 50, 0, 0, 0, 1.0, 1);

  m_mars->SetValues(.5, .2, 5, 5, 1, 0, 0, 1, -1);

  m_venus->SetValues(.5, .3, 5, 5, 1, 0, 0, 1, 1);
  //m_mercury->SetValues();
  //m_jupiter->SetValues();
  //m_neptune->SetValues();
  //m_uranus->SetValues();
  //m_pluto->SetValues();






  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  // Update the planets
  m_Sun->Update(dt, glm::mat4(1.0f));

  m_earth->Update(dt, m_Sun->GetLocation());
  m_moon->Update(dt, m_earth->GetLocation());

  m_saturn->Update(dt, m_Sun->GetLocation());

  m_secret->Update(dt, m_Sun->GetLocation());

  m_mars->Update(dt, m_secret->GetLocation());

  m_venus->Update(dt,m_secret->GetLocation());

}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


  // Render the objects
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_Sun->GetModel()));

  m_Sun->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_earth->GetModel()));

  m_earth->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_moon->GetModel()));

  m_moon->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_saturn->GetModel()));

  m_saturn->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_secret->GetModel()));

  m_secret->Render();


    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mars->GetModel()));

  m_mars->Render();

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_venus->GetModel()));

  m_venus->Render();
  /*

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mercury->GetModel()));

  m_mercury->Render();

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_jupiter->GetModel()));

  m_jupiter->Render();

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_neptune->GetModel()));

  m_neptune->Render();

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_uranus->GetModel()));

  m_uranus->Render();

     glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pluto->GetModel()));

  m_pluto->Render();

  */









  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

void Graphics::IncSimSpeed()
{
  m_secret->IncreaseRotationSpeed();
  m_secret->IncreaseOrbitSpeed();

  m_Sun->IncreaseRotationSpeed();
  m_Sun->IncreaseOrbitSpeed();

  m_earth->IncreaseRotationSpeed();
  m_earth->IncreaseOrbitSpeed();

  m_moon->IncreaseRotationSpeed();
  m_moon->IncreaseOrbitSpeed();

  m_saturn->IncreaseOrbitSpeed();
  m_saturn->IncreaseRotationSpeed();




  m_mars->IncreaseRotationSpeed();
  m_mars->IncreaseOrbitSpeed();

  m_venus->IncreaseRotationSpeed();
  m_venus->IncreaseOrbitSpeed();
/*
  m_mercury->IncreaseRotationSpeed();
  m_mercury->IncreaseOrbitSpeed();

  m_jupiter->IncreaseRotationSpeed();
  m_jupiter->IncreaseOrbitSpeed();

  m_neptune->IncreaseRotationSpeed();
  m_neptune->IncreaseOrbitSpeed();

  m_uranus->IncreaseRotationSpeed();
  m_uranus->IncreaseOrbitSpeed();

  m_pluto->IncreaseRotationSpeed();
  m_pluto->IncreaseOrbitSpeed();
   *
   */
}

void Graphics::DecSimSpeed()
{
  m_secret->DecreaseOrbitSpeed();
  m_secret->DecreaseRoationSpeed();

  m_Sun->DecreaseRoationSpeed();
  m_Sun->DecreaseOrbitSpeed();

  m_earth->DecreaseRoationSpeed();
  m_earth->DecreaseOrbitSpeed();

  m_moon->DecreaseRoationSpeed();
  m_moon->DecreaseOrbitSpeed();

  m_saturn->DecreaseRoationSpeed();
  m_saturn->DecreaseOrbitSpeed();


  m_mars->DecreaseRoationSpeed();
  m_mars->DecreaseOrbitSpeed();

  m_venus->DecreaseRoationSpeed();
  m_venus->DecreaseOrbitSpeed();
/*
  m_mercury->DecreaseRoationSpeed();
  m_mercury->DecreaseOrbitSpeed();

  m_jupiter->DecreaseRoationSpeed();
  m_jupiter->DecreaseOrbitSpeed();

  m_neptune->DecreaseRoationSpeed();
  m_neptune->DecreaseOrbitSpeed();

  m_uranus->DecreaseRoationSpeed();
  m_uranus->DecreaseOrbitSpeed();

  m_pluto->DecreaseRoationSpeed();
  m_pluto->DecreaseOrbitSpeed();

   */
}

void Graphics::resetAll()
{
  m_secret->ResetAll();

  m_Sun->ResetAll();

  m_earth->ResetAll();

  m_moon->ResetAll();

  m_saturn->ResetAll();


  m_mars->ResetAll();

  m_venus->ResetAll();
/*
  m_mercury->ResetAll();

  m_jupiter->ResetAll();

  m_neptune->ResetAll();

  m_uranus->ResetAll();

  m_pluto-> ResetAll();
   */
}
