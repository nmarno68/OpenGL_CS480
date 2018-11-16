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
  numBallsLeft = 3;
  m_ballInPlay = false;



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

  m_ballPos = m_phong->GetUniformLocation("ballPos");
  if (m_ballPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ballPos not found\n");
    return false;
  }

  m_spotlight_size = m_phong->GetUniformLocation("spotlight_size");
  if (m_spotlight_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_spotlight_size not found\n");
    return false;
  }

  m_spotlight_brightness = m_phong->GetUniformLocation("spotlight_bright");
  if (m_spotlight_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_spotlight_brightness not found\n");
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

  m_hard_edge = m_phong->GetUniformLocation("hard_edge");
  if (m_hard_edge == INVALID_UNIFORM_LOCATION)
  {
    printf("m_hard_edge not found\n");
    return false;
  }

  m_ambient_color = m_phong->GetUniformLocation("ambient_color");
  if (m_ambient_color == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambient_color not found\n");
    return false;
  }

  //bumper 1
  m_bumper1 = m_phong->GetUniformLocation("bumper1");
  if (m_bumper1 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_bumper1_c = m_phong->GetUniformLocation("bumper1_c");
  if (m_bumper1_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
    return false;
  }

  //bumper2
  m_bumper2 = m_phong->GetUniformLocation("bumper2");
  if (m_bumper2 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_bumper2_c = m_phong->GetUniformLocation("bumper2_c");
  if (m_bumper2_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
    return false;
  }

  //bumper3
  m_bumper3 = m_phong->GetUniformLocation("bumper3");
  if (m_bumper3 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_bumper3_c = m_phong->GetUniformLocation("bumper3_c");
  if (m_bumper3_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
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

  m_gballPos = m_gourand->GetUniformLocation("ballPos");
  if (m_gballPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ballPos not found\n");
    return false;
  }

  m_gspotlight_size = m_gourand->GetUniformLocation("spotlight_size");
  if (m_gspotlight_size == INVALID_UNIFORM_LOCATION)
  {
    printf("m_spotlight_size not found\n");
    return false;
  }

  m_gspotlight_brightness = m_gourand->GetUniformLocation("spotlight_bright");
  if (m_gspotlight_brightness == INVALID_UNIFORM_LOCATION)
  {
    printf("m_spotlight_brightness not found\n");
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

  m_ghard_edge = m_gourand->GetUniformLocation("hard_edge");
  if (m_ghard_edge == INVALID_UNIFORM_LOCATION)
  {
    printf("m_hard_edge not found\n");
    return false;
  }

  m_gambient_color = m_gourand->GetUniformLocation("ambient_color");
  if (m_gambient_color == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambient_color not found\n");
    return false;
  }

  //bumper 1
  m_gbumper1 = m_gourand->GetUniformLocation("bumper1");
  if (m_gbumper1 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_gbumper1_c = m_gourand->GetUniformLocation("bumper1_c");
  if (m_gbumper1_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
    return false;
  }

  //bumper2
  m_gbumper2 = m_gourand->GetUniformLocation("bumper2");
  if (m_gbumper2 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_gbumper2_c = m_gourand->GetUniformLocation("bumper2_c");
  if (m_gbumper2_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
    return false;
  }

  //bumper3
  m_gbumper3 = m_gourand->GetUniformLocation("bumper3");
  if (m_gbumper3 == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1 not found\n");
    return false;
  }

  m_gbumper3_c = m_gourand->GetUniformLocation("bumper3_c");
  if (m_gbumper3_c == INVALID_UNIFORM_LOCATION)
  {
    printf("m_bumper1_c not found\n");
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



  //initialize lighting values
  spotlight_size = 250; //initialize to no spotlight
  spotlight_brightness = .7; //cause this amount looks nice
  ambientStrength = .3; //cause this also looks nice
  spot = false;
  hard_edge = true;
  phong = true;
  ambient_color = glm::vec3(1.0, 1.0, 1.0);

  //Creating physics world
  m_broadphase = new btDbvtBroadphase();
  m_collisionConfiguration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
  m_solver = new btSequentialImpulseConstraintSolver();

  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

  m_dynamicsWorld->setGravity(btVector3(-.05, -.05, 0));


//Initializing objects
// 1 -> plane, 2 -> sphere, 3 -> cylinder, 4 -> cube, 9 -> triangle mesh
  //std::string filename, int shape, bool needsLoading, float s_x, float s_y, float s_z, int flipper);

  m_boardy = new Object("PinballBoard.obj", 9, true, 1, 1.5, 1, 0);
  m_cyl = new Object("CylinderBumper.obj", 9, true, .2, .2, .2, 0);
  m_ball = new Object("UglySphere.obj", 2, true, 1, 1, 1, 0);
  m_cube = new Object("CylinderBumper.obj", 9, true, .2, .2, .2, false);
  m_backsplash = new Object("PinballBacksplash.obj", -1, true, 1.9, 2, 1.9, 0);
  m_bumper = new Object("CylinderBumper.obj", 9, true, .2, .2, .2, 0);

  m_triangle_left = new Object("triangleBumpers.obj", 9, true, .3, .7, .3, 0);
  m_triangle_right = new Object("triangleBumpers.obj", 9, true, .3, .7, .3,0);

  m_flipper_left = new Object("flippers.obj", 9, true, .15, .25, .15, 1);
  m_flipper_right = new Object("flipper2.obj", 9, true, .15, .25, .15, 2);

  m_engage = new Object("Button.obj", -1, true, .2, .2, .2, 0);
  m_plunger = new Object("plunger.obj", -1, true, .1, .2, .2, 0);

   // m_leftWall = new Object("none", 5, false);
   // m_rightWall = new Object("none", 6, false);
   // m_topWall = new Object("none", 7, false);
   m_bottomWall = new Object("none", 8, false, 1, 1, 1, 0);


  //specular_brightness, specular_size (only on rendered objects)
  m_boardy->SetValues(.5, 50);
  m_cyl->SetValues(.7, 150);
  m_ball->SetValues(.7, 150);
  m_cube->SetValues(.7, 150);
  m_backsplash->SetValues(.5, 150);
  m_bumper->SetValues(.7, 150);
  m_engage->SetValues(.7, 150);
  m_plunger->SetValues(.8, 200);

  m_triangle_left->SetValues(.7, 150);
  m_triangle_right->SetValues(.7, 150);

  m_flipper_left->SetValues(.7, 150);
  m_flipper_right->SetValues(.7, 150);


//Initializing object physics

  //inertia vector

  //SetBullet - mass, inertia, kinObject , physics, initial_translate, initial rotate, restitution, friction
  glm::vec3 v(0, 0, 0);
  m_boardy->SetBullet(0, v, true, true, glm::vec3(0, 0, 0), 0, 0, 1);

  v = glm::vec3(0, 0, 0);
  m_cyl->SetBullet(0, v, true, true, glm::vec3(1.0, .25, 0), 0, 1.5, 0);

  v = glm::vec3(0, 0, 0);
  m_ball->SetBullet(1, v, false, true, glm::vec3(-3, .25, 2.0), 0, 1, 1);

  v = glm::vec3(0, 0, 0);
  m_cube->SetBullet(0, v, true, true, glm::vec3(0, .25, -.75), 0, 1.5, 0);

  m_bumper->SetBullet(0, v, true, true, glm::vec3(-.25, .25, .4), 0, 1.5, 0);

  m_triangle_right->SetBullet(0, v, true, true, glm::vec3(-2.1, 0.2, .4), -M_PI / 4, 1.5, 0);
  m_triangle_left->SetBullet(0, v, true, true, glm::vec3(-2.1, 0.2, -1.3), M_PI * 2.0, 1.5, 0);

  m_backsplash->SetBullet(0, v, true, false, glm::vec3(5.5, 3.0, -0.15), M_PI, 0, 0);

  m_engage->SetBullet(0, v, true, false, glm::vec3(-3.6, 1.0, 1.2), 0, 0, 0);


  m_plunger->SetBullet(0, v, true, false, glm::vec3(-4.4, .65, 2.0), 0, 0, 0);



  m_flipper_right->SetBullet(0, v, true, true, glm::vec3(-2.95, 0.11, .32), M_PI / 20, .2, 3);
  m_flipper_left->SetBullet(0, v, true, true, glm::vec3(-2.95, 0.11, -1.2), -M_PI / 20, .2, 3);


	//m_leftWall->SetBullet(1, v, true, true, glm::vec3(0, 0, 1.05));
	//m_rightWall->SetBullet(1, v, true, true, glm::vec3(0, 0, -1.05));
	//m_topWall->SetBullet(1, v, true, true, glm::vec3(2.05, 0, 0));
	m_bottomWall->SetBullet(0, v, true, true, glm::vec3(0.0, .3, 0), 0, 0, 0);

  short mask = 0b11111111;

  //Add to dynamics world
  m_dynamicsWorld->addRigidBody(m_bottomWall->GetRigidBody(), mask, mask);

  m_dynamicsWorld->addRigidBody(m_boardy->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_cyl->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_ball->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_cube->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_bumper->GetRigidBody(), mask, mask);

  m_dynamicsWorld->addRigidBody(m_triangle_right->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_triangle_left->GetRigidBody(), mask, mask);

  m_dynamicsWorld->addRigidBody(m_flipper_right->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_flipper_left->GetRigidBody(), mask, mask);

	//m_dynamicsWorld->addRigidBody(m_leftWall->GetRigidBody(), mask, mask);
	//m_dynamicsWorld->addRigidBody(m_rightWall->GetRigidBody(), mask, mask);
	//m_dynamicsWorld->addRigidBody(m_topWall->GetRigidBody(), mask, mask);




	//Additional Light Sources
	b_1 = new lightSource(glm::vec3 (1.0, 0.0, 0.0), glm::vec3(1.0, .25, 0) + glm::vec3(0.0, 0.5, 0.0));
	b_2 = new lightSource(glm::vec3 (0.0, 1.0, 0.0), glm::vec3(0, .25, -.75) + glm::vec3(0.0, 0.5, 0.0));
	b_3 = new lightSource(glm::vec3 (0.0, 0.5, 1.0), glm::vec3(-.25, .25, .4) + glm::vec3(0.0, 0.5, 0.0));

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  if(!numBallsLeft)
  {
    EndGame();
  }

  if(IsBallOver())
  {
    m_ball->ResetBall();
    m_ballInPlay = false;
    numBallsLeft--;
  }

  m_dynamicsWorld->stepSimulation(dt, 10);

  //call object updates and camera updates
  m_boardy->Update(dt, glm::mat4(1.0f), 1);
  m_cyl->Update(dt, glm::mat4(1.0f), 1);
  m_ball->Update(dt, glm::mat4(1.0f), .125);
  m_cube->Update(dt, glm::mat4(1.0f), 1);
  m_bumper->Update(dt, glm::mat4(1.0f), 1);

  m_triangle_left->Update(dt, glm::mat4(1.0f), 1);
  m_triangle_right->Update(dt, glm::mat4(1.0f), 1);

  m_flipper_right->Update(dt, glm::mat4(1.0f), 1);
  m_flipper_left->Update(dt, glm::mat4(1.0f), 1);

  m_backsplash->Update(dt, glm::mat4(1.0f), 1);
  m_engage->Update(dt, glm::mat4(1.0f), 1);
  m_plunger->Update(dt, glm::mat4(1.0f), 1);

}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(phong) {
    // Start the correct program
    m_phong->Enable();

    //Send in bunmper 1 light source
    glUniform3fv(m_bumper1, 1, glm::value_ptr(b_1->pos));     //Position
    glUniform3fv(m_bumper1_c, 1, glm::value_ptr(b_1->color)); //Color

    glUniform3fv(m_bumper2, 1, glm::value_ptr(b_2->pos));     //Position
    glUniform3fv(m_bumper2_c, 1, glm::value_ptr(b_2->color)); //Color

    glUniform3fv(m_bumper3, 1, glm::value_ptr(b_3->pos));     //Position
    glUniform3fv(m_bumper3_c, 1, glm::value_ptr(b_3->color)); //Color

    //Send in ambient color
    glUniform3fv(m_ambient_color, 1, glm::value_ptr(ambient_color));

    //sending in camera position for specular lighting
    glUniform3fv(m_viewPos, 1, glm::value_ptr(m_camera->cameraPosition));

    //sending in ball position for spotlight
    glUniform3fv(m_ballPos, 1, glm::value_ptr(m_ball->GetLocationVector()));

    //Sending Spotlight stuff
    //spotlight brightness
    glUniform1f(m_spotlight_brightness, (GLfloat) spotlight_brightness);

    //spotlight size
    if (spot) {
      glUniform1f(m_spotlight_size, (GLfloat) spotlight_size);  //lower means bigger
    }
    else {
      glUniform1f(m_spotlight_size, (GLfloat) 0);
    }
    //hard edge or soft edge
    glUniform1i(m_hard_edge, hard_edge);

    //ambient strength
    glUniform1f(m_ambientStrength, (GLfloat) ambientStrength);

    //Sending in view and projection
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


    //send in model matrices and render the objects
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_boardy->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_boardy->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_boardy->specular_size);
    m_boardy->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cyl->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_cyl->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_cyl->specular_size);
    m_cyl->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_ball->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_ball->specular_size);
    m_ball->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_cube->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_cube->specular_size);
    m_cube->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_bumper->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_bumper->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_bumper->specular_size);
    m_bumper->Render();


    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_triangle_left->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_triangle_left->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_triangle_left->specular_size);
    m_triangle_left->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_triangle_right->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_triangle_right->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_triangle_right->specular_size);
    m_triangle_right->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipper_right->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_flipper_right->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_flipper_right->specular_size);
    m_flipper_right->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipper_left->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_flipper_left->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_flipper_left->specular_size);
    m_flipper_left->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_plunger->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_plunger->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_plunger->specular_size);
    m_plunger->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_backsplash->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_backsplash->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_backsplash->specular_size);
    m_backsplash->meshes[1].Draw();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_engage->GetModel()));
    glUniform1f(m_specular_brightness, (GLfloat) m_engage->specular_brightness);
    glUniform1i(m_specular_size, (GLint) m_engage->specular_size);
    m_engage->meshes[0].Draw();

    m_texture->Enable();
    glUniformMatrix4fv(m_tprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_tviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
    glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_backsplash->GetModel()));
    m_backsplash->meshes[0].Draw();

    glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_engage->GetModel()));
    m_engage->meshes[1].Draw();

  }



  else
  {
    m_gourand->Enable();


    glUniform3fv(m_gbumper1, 1, glm::value_ptr(b_1->pos));     //Position
    glUniform3fv(m_gbumper1_c, 1, glm::value_ptr(b_1->color)); //Color

    glUniform3fv(m_gbumper2, 1, glm::value_ptr(b_2->pos));     //Position
    glUniform3fv(m_gbumper2_c, 1, glm::value_ptr(b_2->color)); //Color

    glUniform3fv(m_gbumper3, 1, glm::value_ptr(b_3->pos));     //Position
    glUniform3fv(m_gbumper3_c, 1, glm::value_ptr(b_3->color)); //Color

    //Send in ambient color
    glUniform3fv(m_gambient_color, 1, glm::value_ptr(ambient_color));

    //sending in camera position for specular lighting
    glUniform3fv(m_gviewPos, 1, glm::value_ptr(m_camera->cameraPosition));

    //sending in ball position for spotlight
    glUniform3fv(m_gballPos, 1, glm::value_ptr(m_ball->GetLocationVector()));

    //Sending Spotlight stuff
    //spotlight brightness
    glUniform1f(m_gspotlight_brightness, (GLfloat) spotlight_brightness);

    //spotlight size
    if (spot) {
      glUniform1f(m_gspotlight_size, (GLfloat) spotlight_size);  //lower means bigger
    }
    else {
      glUniform1f(m_gspotlight_size, (GLfloat) 0);
    }
    //hard edge or soft edge
    glUniform1i(m_ghard_edge, hard_edge);

    //ambient strength
    glUniform1f(m_gambientStrength, (GLfloat) ambientStrength);

    //Sending in view and projection
    glUniformMatrix4fv(m_gprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_gviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


    //send in model matrices and render the objects
    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_boardy->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_boardy->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_boardy->specular_size);
    m_boardy->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_cyl->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_cyl->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_cyl->specular_size);
    m_cyl->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_ball->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_ball->specular_size);
    m_ball->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_cube->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_cube->specular_size);
    m_cube->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_bumper->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_bumper->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_bumper->specular_size);
    m_bumper->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipper_right->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_flipper_right->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_flipper_right->specular_size);
    m_flipper_right->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipper_left->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_flipper_left->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_flipper_left->specular_size);
    m_flipper_left->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_triangle_left->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_triangle_left->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_triangle_left->specular_size);
    m_triangle_left->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_triangle_right->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_triangle_right->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_triangle_right->specular_size);
    m_triangle_right->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_plunger->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_plunger->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_plunger->specular_size);
    m_plunger->Render();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_backsplash->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_backsplash->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_backsplash->specular_size);
    m_backsplash->meshes[1].Draw();

    glUniformMatrix4fv(m_gmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_engage->GetModel()));
    glUniform1f(m_gspecular_brightness, (GLfloat) m_engage->specular_brightness);
    glUniform1i(m_gspecular_size, (GLint) m_engage->specular_size);
    m_engage->meshes[0].Draw();

    m_texture->Enable();
    glUniformMatrix4fv(m_tprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_tviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
    glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_backsplash->GetModel()));
    m_backsplash->meshes[0].Draw();

    glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_engage->GetModel()));
    m_engage->meshes[1].Draw();

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

bool Graphics::IsBallOver()
{
  glm::vec3 ballLocation = m_ball->GetLocationVector();
  if(ballLocation.x < -3.68 and ballLocation.z < .32 and ballLocation.z > -1.2)
    return true;

  return false;
}

void Graphics::EndGame()
{
  if(ImGui::Button("Replay"))
    numBallsLeft = 3;
}
