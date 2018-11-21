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


  //
  //Initializing phong lighting shader
  //
  m_phong = new Shader();
  if(!m_phong->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_phong->AddShader(GL_VERTEX_SHADER, "phongShaders"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_phong->AddShader(GL_FRAGMENT_SHADER, "phongShaders"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_phong->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }


  //
  //Initializing the gourand lighting shader
  //
  m_gourand = new Shader();
  if(!m_gourand->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_gourand->AddShader(GL_VERTEX_SHADER, "gourandShaders"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_gourand->AddShader(GL_FRAGMENT_SHADER, "gourandShaders"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_gourand->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }




  //
  //Initializing the texture lighting shader
  //
  m_texture = new Shader();
  if(!m_texture->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_texture->AddShader(GL_VERTEX_SHADER, "textureShaders"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_texture->AddShader(GL_FRAGMENT_SHADER, "textureShaders"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_texture->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }





  //
  //Locating uniforms in the phong shader
  //
  m_projectionMatrix = m_phong->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  m_viewMatrix = m_phong->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  m_modelMatrix = m_phong->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_viewPos = m_phong->GetUniformLocation("viewPos");
  if (m_viewPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewPos not found\n");
    return false;
  }

  m_specular_brightness = m_phong->GetUniformLocation("specularStrength");
  if (m_specular_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_specular_brightness not found\n");
    return false;
  }

  m_specular_size = m_phong->GetUniformLocation("glint_radius");
  if (m_specular_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_specular_size not found\n");
    return false;
  }

  m_ambientStrength = m_phong->GetUniformLocation("ambientStrength");
  if (m_ambientStrength == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambientStrength not found\n");
    return false;
  }

  m_ambient_color = m_phong->GetUniformLocation("ambient_color");
  if (m_ambient_color == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambient_color not found\n");
    return false;
  }










  //
  //Locating uniforms in the gourand shader
  //
  m_gprojectionMatrix = m_gourand->GetUniformLocation("projectionMatrix");
  if (m_gprojectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  m_gviewMatrix = m_gourand->GetUniformLocation("viewMatrix");
  if (m_gviewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  m_gmodelMatrix = m_gourand->GetUniformLocation("modelMatrix");
  if (m_gmodelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_gviewPos = m_gourand->GetUniformLocation("viewPos");
  if (m_gviewPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewPos not found\n");
    return false;
  }

  m_gspecular_brightness = m_gourand->GetUniformLocation("specularStrength");
  if (m_gspecular_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_specular_brightness not found\n");
    return false;
  }

  m_gspecular_size = m_gourand->GetUniformLocation("glint_radius");
  if (m_gspecular_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_specular_size not found\n");
    return false;
  }

  m_gambientStrength = m_gourand->GetUniformLocation("ambientStrength");
  if (m_gambientStrength == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambientStrength not found\n");
    return false;
  }

  m_gambient_color = m_gourand->GetUniformLocation("ambient_color");
  if (m_gambient_color == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambient_color not found\n");
    return false;
  }









  //INitializing texture shader stuff
  m_tprojectionMatrix = m_texture->GetUniformLocation("projectionMatrix");
  if (m_tprojectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  m_tviewMatrix = m_texture->GetUniformLocation("viewMatrix");
  if (m_tviewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  m_tmodelMatrix = m_texture->GetUniformLocation("modelMatrix");
  if (m_tmodelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }


  normals = true;

  //initialize lighting values
  ambientStrength = .7; //cause this also looks nice
  phong = true;
  ambient_color = glm::vec3(1.0, .8, .9);
  skybox_used = 1;

  //Creating physics world
  m_broadphase = new btDbvtBroadphase();
  m_collisionConfiguration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
  m_solver = new btSequentialImpulseConstraintSolver();

  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

  m_dynamicsWorld->setGravity(btVector3(-.05, -.05, 0));


  //Initializing objects
  // int shape: 1 -> plane, 2 -> sphere, 3 -> cylinder, 4 -> cube, 9 -> triangle mesh
  //std::string filename, int shape, bool needsLoading, float s_x, float s_y, float s_z, int flipper)
  //filename, what shape the bullet primitive is or triangle meshes, whether or not there is an object file to load, scaling variables, whether or not
  //the object is a flipper (0->not a flipper, 1-left flipper, 2-right flipper

  m_ground = new Object("ground.obj", -1, true, 1.0, 1.0, 1.0, 0);
  m_skybox = new Object("skybox.obj", -1, true, 80, 80, 80, 0);
  m_skyboxSunset = new Object("sunsetBox.obj", -1, true, 80, 80, 80, 0);



  //specular_brightness, specular_size (only on rendered objects)
  m_ground->SetValues(.1, 10);
  m_skybox->SetValues(.1, 10);
  m_skyboxSunset->SetValues(.1, 10);


  //Initializing object physics
  //inertia vector
  glm::vec3 v = glm::vec3(0.0, 0.0, 0.0);

  //SetBullet - mass, inertia, kinObject , physics, initial_translate, initial rotate, restitution, friction
  m_ground->SetBullet(0, v, false, false, glm::vec3(0.0, 0.0, 0.0), 0, 0, 0);
  m_skybox->SetBullet(0, v, false, false, m_camera->cameraPosition + glm::vec3(0.0, -10.0, 0.0), M_PI, 0, 0);
  m_skyboxSunset->SetBullet(0, v, false, false, m_camera->cameraPosition + glm::vec3(0.0, 0.0, 0.0), 0, 0, 0);



  short mask = 0b11111111;

  //Add to dynamics world







	//Additional Light Sources


  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  m_ground->Update(dt, glm::mat4(1.0f), 1);
  switch(skybox_used) {
    case 1:
      m_skybox->Update(dt, m_camera->GetLocationSkybox(skybox_used), 1);
      break;
    case 2:
      m_skyboxSunset->Update(dt, m_camera->GetLocationSkybox(skybox_used), 1);
      break;
  }

}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Start the correct program
    if(normals) {
      if (phong) {
        m_phong->Enable();


        //Send in ambient color
        glUniform3fv(m_ambient_color, 1, glm::value_ptr(ambient_color));

        //sending in camera position for specular lighting
        glUniform3fv(m_viewPos, 1, glm::value_ptr(m_camera->cameraPosition));

        //ambient strength
        glUniform1f(m_ambientStrength, (GLfloat) ambientStrength);

        //Sending in view and projection
        glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
        glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

        //send in model matrices, specular size and specular brightness and render the objects
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_ground->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_ground->specular_size);
        m_ground->Render();
      }

      else {
        glUniform3fv(m_gambient_color, 1, glm::value_ptr(ambient_color));

        //sending in camera position for specular lighting
        glUniform3fv(m_gviewPos, 1, glm::value_ptr(m_camera->cameraPosition));

        //ambient strength
        glUniform1f(m_gambientStrength, (GLfloat) ambientStrength);

        //Sending in view and projection
        glUniformMatrix4fv(m_gprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
        glUniformMatrix4fv(m_gviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

        //send in model matrices, specular size and specular brightness and render the objects
        glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->GetModel()));
        glUniform1f(m_gspecular_brightness, (GLfloat) m_ground->specular_brightness);
        glUniform1i(m_gspecular_size, (GLint) m_ground->specular_size);
        m_ground->Render();

      }
    }
    else{
      m_texture->Enable();
      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->GetModel()));
      m_ground->Render();
    }
    m_texture->Enable();


  glUniformMatrix4fv(m_tprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_tviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  //glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->GetModel()));
  //m_ground->Render();

  switch(skybox_used) {
    case 1:
      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_skybox->GetModel()));
      m_skybox->Render();
      break;
    case 2:
      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_skyboxSunset->GetModel()));
      m_skyboxSunset->Render();
      break;
  }







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

