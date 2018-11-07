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




  //initializing camera view flags
  scaled_view = false;
  top_view = false;

  //Initializing phong lighting shader
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




  //Locating uniforms in the phong shader
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
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_ballPos = m_phong->GetUniformLocation("ballPos");
  if (m_ballPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_spotlight_size = m_phong->GetUniformLocation("spotlight_size");
  if (m_spotlight_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_spotlight_brightness = m_phong->GetUniformLocation("spotlight_bright");
  if (m_spotlight_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_specular_brightness = m_phong->GetUniformLocation("specularStrength");
  if (m_specular_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_specular_size = m_phong->GetUniformLocation("glint_radius");
  if (m_specular_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }





  //Creating physics world
  m_broadphase = new btDbvtBroadphase();
  m_collisionConfiguration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
  m_solver = new btSequentialImpulseConstraintSolver();

  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

  m_dynamicsWorld->setGravity(btVector3(0, -.05, 0));


//Initializing objects
// 1 -> plane, 2 -> sphere, 3 -> cylinder, 4 -> cube

  m_boardy = new Object("UglyBoard.obj", 1, true);
  m_cyl = new Object("UglyCylinder.obj", 3, true);
  m_ball = new Object("UglySphere.obj", 2, true);
  m_cube = new Object("UglyCube.obj", 4, true);
  m_leftWall = new Object("none", 5, false);
  m_rightWall = new Object("none", 6, false);
  m_topWall = new Object("none", 7, false);
  m_bottomWall = new Object("none", 8, false);


  //SetValues scale_x, scale_y, scale_z
  m_boardy->SetValues(1.0, 2.0, 1.0);
  m_cyl->SetValues(.3, .3, .3);
  m_ball->SetValues(1, 1, 1);
  m_cube->SetValues(1, 1, 1);

//Initializing object physics

  //inertia vector

  //SetBullet - mass, inertia, kinObject , physics, initial_translate
  glm::vec3 v(0, 0, 0);
  m_boardy->SetBullet(0, v, true, true, glm::vec3(0, 0, 0));

  v = glm::vec3(0, 0, 0);
  m_cyl->SetBullet(0, v, true, true, glm::vec3(0, 0, 0));

  v = glm::vec3(0, 0, 0);
  m_ball->SetBullet(1, v, false, true, glm::vec3(0, .5, .75));

  v = glm::vec3(0, 0, 0);
  m_cube->SetBullet(1, v, false, true, glm::vec3(0, .5, -.75));

	m_leftWall->SetBullet(1, v, true, true, glm::vec3(0, 0, 1.05));
	m_rightWall->SetBullet(1, v, true, true, glm::vec3(0, 0, -1.05));
	m_topWall->SetBullet(1, v, true, true, glm::vec3(2.05, 0, 0));
	m_bottomWall->SetBullet(1, v, true, true, glm::vec3(-2.05, 0, 0));

  short mask = 0b11111111;

  //Add to dynamics world
  m_dynamicsWorld->addRigidBody(m_boardy->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_cyl->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_ball->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_cube->GetRigidBody(), mask, mask);

	m_dynamicsWorld->addRigidBody(m_leftWall->GetRigidBody(), mask, mask);
	m_dynamicsWorld->addRigidBody(m_rightWall->GetRigidBody(), mask, mask);
	m_dynamicsWorld->addRigidBody(m_topWall->GetRigidBody(), mask, mask);
	m_dynamicsWorld->addRigidBody(m_bottomWall->GetRigidBody(), mask, mask);




  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  m_dynamicsWorld->stepSimulation(dt, 10);

  //call object updates and camera updates
  m_boardy->Update(dt, glm::mat4(1.0f), 1);
  m_cyl->Update(dt, glm::mat4(1.0f), .25);
  m_ball->Update(dt, glm::mat4(1.0f), .125);
  m_cube->Update(dt, glm::mat4(1.0f), .125);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
    m_phong->Enable();


  // Send in the projection and view to the shader
  //sending in camera position for specular lighting
  glUniform3fv(m_viewPos, 1, glm::value_ptr(m_camera->cameraPosition));

  //sending in ball position for spotlight
  glUniform3fv(m_ballPos, 1, glm::value_ptr(m_ball->GetLocationVector()));

  //Sending specular values (just once for testing)
  //specular brightness (float)
  glUniform1f(m_specular_brightness, (GLfloat) .7);

  //specular radius thing (int)
  glUniform1i(m_specular_size, (GLint) 200);

  //Sending Spotlight stuff
  //spotlight brightness
  glUniform1f(m_spotlight_brightness, (GLfloat) .7);

  //spotlight size
  glUniform1i(m_spotlight_size, (GLint) 5);  //lower means bigger


  //Sending in view and projection
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


  //send in model matrices and render the objects
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_boardy->GetModel()));
  m_boardy->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cyl->GetModel()));
  m_cyl->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
  m_ball->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  m_cube->Render();




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


