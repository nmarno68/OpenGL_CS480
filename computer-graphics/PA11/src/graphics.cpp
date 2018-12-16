#include "graphics.h"
#define NUM_SPELLS 6
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
  //Initializing the color shader
  //
  m_color = new Shader();
  if(!m_color->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_color->AddShader(GL_VERTEX_SHADER, "ColorShader"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_color->AddShader(GL_FRAGMENT_SHADER, "ColorShader"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_color->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }



  //
  //Locating uniforms in the color shader
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

  m_lightDirection = m_phong->GetUniformLocation("lightDirection");
  if (m_lightDirection == INVALID_UNIFORM_LOCATION)
  {
    printf("m_lightDirection not found\n");
    return false;
  }

  m_lightColor = m_phong->GetUniformLocation("lightColor");
  if (m_lightColor == INVALID_UNIFORM_LOCATION)
  {
    printf("m_lightColor not found\n");
    return false;
  }

  m_pointSourceColor = m_phong->GetUniformLocation("lightSourceColor");
  if(m_pointSourceColor == INVALID_UNIFORM_LOCATION)
  {
    printf("m_pointSourceColor not found\n");
    return false;
  }

  m_pointSources = m_phong->GetUniformLocation("pointSources");
  if(m_pointSources == INVALID_UNIFORM_LOCATION)
  {
    printf("m_pointSource not found\n");
    return false;
  }

  m_calcSpellLight = m_phong->GetUniformLocation("calcLightSource");
  if(m_calcSpellLight == INVALID_UNIFORM_LOCATION)
  {
    printf("m_calcSpellLight not found\n");
    return false;
  }

  m_useNorm = m_phong->GetUniformLocation("useNorm");
  if(m_useNorm == INVALID_UNIFORM_LOCATION)
  {
    printf("m_useNorm not found\n");
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


  //
 //color shader uniforms
//
  m_cPM = m_color->GetUniformLocation("projectionMatrix");
  if(m_cPM == INVALID_UNIFORM_LOCATION)
  {
    printf("m_cPM not found\n");
    return false;
  }

  m_cVM = m_color->GetUniformLocation("viewMatrix");
  if(m_cVM == INVALID_UNIFORM_LOCATION)
  {
    printf("m_cVM not found\n");
    return false;
  }

  m_cMM = m_color->GetUniformLocation("modelMatrix");
  if(m_cMM == INVALID_UNIFORM_LOCATION)
  {
    printf("m_cMM not found\n");
    return false;
  }

  m_cColor = m_color->GetUniformLocation("color");
  if(m_cColor == INVALID_UNIFORM_LOCATION)
  {
    printf("m_cColor not found\n");
    return false;
  }

  m_cCamPos = m_color->GetUniformLocation("cameraPos");
  if(m_cCamPos == INVALID_UNIFORM_LOCATION)
  {
    printf("m_cCamPos not found\n");
    return false;
  }













  normals = true;

  //initialize lighting values
  ambientStrength = .3; //cause this also looks nice
  phong = true;
  ambient_color = glm::vec3(1.0, 1.0, 1.0);
  skybox_used = 1;
  l_C = glm::vec3(1.0, 1.0, 1.0);
  l_D = glm::vec3(0.3, 1.0, 0.0);
  moving = false;
  movement = 'N';
  spellToCast = 3;
  game_running = false;

  //Creating physics world
  m_broadphase = new btDbvtBroadphase();
  m_collisionConfiguration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
  m_solver = new btSequentialImpulseConstraintSolver();

  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

  m_dynamicsWorld->setGravity(btVector3(0, -.1, 0));


  //Initializing objects
  // int shape: 1 -> plane, 2 -> sphere, 3 -> cylinder, 4 -> cube, 9 -> triangle mesh
  //std::string filename, int shape, bool needsLoading, float s_x, float s_y, float s_z, int flipper)
  //filename, what shape the bullet primitive is or triangle meshes, whether or not there is an object file to load, scaling variables, whether or not
  //the object is a flipper (0->not a flipper, 1-left flipper, 2-right flipper

  //tester = new Object(".obj", -1, true, .7, .3, .7, 0);
  //tester = new Object("Grass_02.obj", -1, true, .7, .3, .7, 0);



  m_grass1 = new Object("Grass_02.obj", -1, true, .7, .3, .7, 0);
  m_ground = new Object("map.obj", 9, true, 1.0, 1.0, 1.0, 0);
  m_skybox = new Object("skybox.obj", -1, true, 80, 80, 80, 0);
  m_skyboxSunset = new Object("sunsetBox.obj", -1, true, 80, 80, 80, 0);
  m_tree  = new Object("smolTree.obj", 9, true, .03, .04, .03, 0);
  m_rock1 = new Object("Rock_6.obj", 9, true, .7, .7, .7, 0);
  m_rock2 = new Object("Rock_6.obj", 9, true, .5, .5, .5, 0);
  m_well = new Object("well.obj", 9, true, .9, .9, .9, 0);
  for(int i = 0; i < 5; i++)
  {
    Object* temp = new Object("railing_1.obj", 9, true, 1.5, 1.5, 1.0, 0);
    m_fence.push_back(temp);
  }


  m_wiz1 = new Object("NONE", 2, false, .3, .3, .3, 0);
  m_enemy = new Object("NONE", 2, false, .5, .5, .5, 0);
  m_enemySprite = new Object("wizardTextured.obj", -1, true, .15, .15, .15, 0);




  for(int i = 0; i < NUM_SPELLS; i++) {
    m_spells[i] = new Object("spell_ball.obj", 2, true, 0.1, .1, .1, 0);
  }

  //specular_brightness, specular_size (only on rendered objects)
  //tester->SetValues(.1, 10);

  m_grass1->SetValues(.1, 10);
  m_ground->SetValues(.1, 10);
  m_skybox->SetValues(.1, 10);
  m_skyboxSunset->SetValues(.1, 10);
  m_tree->SetValues(.1, 10);
  m_rock1->SetValues(.1, 10);
  m_rock2->SetValues(.1, 10);
  m_well->SetValues(.1, 10);

  for(int i = 0; i < 5; i++)
  {
    m_fence[i]->SetValues(.5, 50);
  }


  m_wiz1->SetValues(.1, 10);
  m_enemy->SetValues(.1, 10);
  m_enemySprite->SetValues(.1, 10);

  for(int i = 0; i < NUM_SPELLS; i++) {
    m_spells[i]->SetValues(.1, 10);
  }

  //Initializing object physics
  //inertia vector
  glm::vec3 v = glm::vec3(0.0, 0.0, 0.0);


  //SetBullet - mass, inertia, kinObject , physics, initial_translate, initial rotate, restitution, friction
  //tester->SetBullet(0, v, false, false, glm::vec3(2.0, .2, 0.0), 0, 0, 0);

  m_grass1->SetBullet(0, v, false, false, glm::vec3(0.0, .2, 0.0), 0, 0, 0);
  m_ground->SetBullet(0, v, true, true, glm::vec3(0.0, 0.0, 0.0), 0, .5, 3);

  m_skybox->SetBullet(0, v, false, false, m_camera->cameraPosition + glm::vec3(0.0, -10.0, 0.0), M_PI, 0, 0);
  m_skyboxSunset->SetBullet(0, v, false, false, m_camera->cameraPosition + glm::vec3(0.0, 0.0, 0.0), 0, 0, 0);

  m_tree->SetBullet(0, v, true, true, glm::vec3(-1.5, 0.3, 0.0), 0, 0, 0);
  m_rock1->SetBullet(0, v, true, true, glm::vec3(-7.5, 0.3, -7.5), 0, 0, 0);
  m_rock2->SetBullet(0, v, true, true, glm::vec3(5.0, 0.4, 5.0), 0, 0, 0);
  m_well->SetBullet(0, v, true, true, glm::vec3(0.0, 0.5, 0.0), 0, 0, 0);

  float disp = 0;
  for(int i = 0; i < 5; i++)
  {
    m_fence[i]->SetBullet(0, v, true, true, glm::vec3(4.5 - disp, 0.3, 1.5), 0, 0, 0);
    disp += 3.5;
  }

  m_wiz1->SetBullet(1, v, false, true, glm::vec3(-6.0, 0.5, -7.0), 0, 0, 3);
  m_enemy->SetBullet(1, v, false, true, glm::vec3(6.0, .5, 7.0), 0, 0, 3);
  m_enemySprite->SetBullet(0, v, false, false, glm::vec3(0.0, 0.0, 0.0), 0, 0, 0);

  for(int i = 0; i < NUM_SPELLS; i++) {
    m_spells[i]->SetBullet(1, v, false, true, glm::vec3(0.0, 10.0 + 5*i, 1.0), 0, 1.0, 0);
    m_spells[i]->spellCasting = false;
  }






  short mask = 0b11111111;

  //Add to dynamics world
  m_dynamicsWorld->addRigidBody(m_ground->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_tree->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_rock1->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_rock2->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_well->GetRigidBody(), mask, mask);
  for(int i = 0; i < 5; i++) {
    m_dynamicsWorld->addRigidBody(m_fence[i]->GetRigidBody(), mask, mask);
  }

  m_dynamicsWorld->addRigidBody(m_wiz1->GetRigidBody(), mask, mask);
  m_dynamicsWorld->addRigidBody(m_enemy->GetRigidBody(), mask, mask);



  for(int i = 0; i < NUM_SPELLS; i++) {
    m_dynamicsWorld->addRigidBody(m_spells[i]->GetRigidBody(), mask, mask);
  }


	//Additional Light Sources
	for(int i = 0; i < NUM_SPELLS; i++)
  {
	  spell_position[i]=(m_spells[i]->GetLocationVector());
	  spell_casting[i] = 0;
  }

  //UNIQUE SPELL COLORS
  spell_colors[0]=(glm::vec3(0.0, .5, 1.0));
	spell_colors[1]=(glm::vec3(0.0, .1, 1.0));
	spell_colors[2]=(glm::vec3(0.2, 0.0, 1.0));
	spell_colors[3]=(glm::vec3(.6, 0.1, 0.0));
  spell_colors[4]=(glm::vec3(.5, 0.0, 0.0));
  spell_colors[5]=(glm::vec3(.3, 0.0, 0.0));


  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{

  m_dynamicsWorld->stepSimulation(dt, 10);

  if(moving)
  {
    glm::vec3 right = glm::normalize(glm::cross(m_camera->cameraFront, glm::vec3(0.0, 1.0, 0.0)));
    glm::vec3 left = -right;
    switch(movement) {
      case 'f':
        m_wiz1->m_rigidBody->setLinearVelocity(btVector3(m_camera->cameraFront.x, -0.2, m_camera->cameraFront.z) / 3);
      break;
      case 'b':
        m_wiz1->m_rigidBody->setLinearVelocity(-btVector3(m_camera->cameraFront.x, 0.2, m_camera->cameraFront.z) / 3);
        break;
      case 'l':
        m_wiz1->m_rigidBody->setLinearVelocity(btVector3(left.x, -0.2, left.z) / 3);
        break;
      case 'r':
        m_wiz1->m_rigidBody->setLinearVelocity(btVector3(right.x, -0.2, right.z) / 3);
        break;
      default:
        break;
    }
  }
  else
  {
    m_wiz1->m_rigidBody->setAngularVelocity(btVector3(0.0, -.2, 0.0));
    m_wiz1->m_rigidBody->setLinearVelocity(btVector3(0.0, -.2, 0.0));
  }


  glm::vec3 temp = m_wiz1->GetLocationVector() - m_enemy->GetLocationVector();
  m_enemy->m_rigidBody->setLinearVelocity(btVector3(temp.x, -.2, temp.z) /15);



  //Spell zero gravity
  for(int i = 0; i < NUM_SPELLS; i++) {
    m_spells[i]->GetRigidBody()->setGravity(btVector3(0, 0, 0));
  }


  glm::vec2 zeroVec = glm::vec2(0.0, 0.0);

  //tester->Update(dt, glm::mat4(1.0f), 1);

  m_grass1->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_ground->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_tree->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_rock1->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_rock2->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_well->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);

  for(int i = 0; i < 5; i++)
  {
    m_fence[i]->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  }



  switch(skybox_used) {
    case 1:
      m_skybox->Update(dt, m_camera->GetLocationSkybox(skybox_used), 1, false, zeroVec);
      break;
    case 2:
      m_skyboxSunset->Update(dt, m_camera->GetLocationSkybox(skybox_used), 1, false, zeroVec);
      break;
  }

  m_wiz1->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);
  m_enemy->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);

  if(game_running) {
    glm::vec2 rotation;
    rotation.x = m_wiz1->GetLocationVector().x - m_enemy->GetLocationVector().x;
    rotation.y = m_wiz1->GetLocationVector().z - m_enemy->GetLocationVector().z;
    m_enemySprite->Update(dt, m_enemy->GetLocation(), 1, true, rotation);


    if (m_enemySprite->Cast()) {
      if (spellToCast == 6) {
        spellToCast = 3;
      }

      m_spells[spellToCast]->EndCast();

      glm::vec3 tempDir = normalize(m_wiz1->GetLocationVector() - m_enemy->GetLocationVector());

      m_spells[spellToCast]->BeginCast(btVector3(tempDir.x, 0.0, tempDir.z) * 5,
                                       btVector3(m_enemySprite->GetLocationVector().x,
                                                 m_enemySprite->GetLocationVector().y + .5,
                                                 m_enemySprite->GetLocationVector().z));

      spellToCast++;
    }
    m_camera->PlanetView(m_wiz1->GetLocationVector(), glm::vec3(0.0, .75, 0.0));
  }
  else
  {
    m_camera->menuView(dt);
  }




  for(int i = 0; i < NUM_SPELLS; i++)
  {
    if (m_spells[i]->spellCasting) {
      m_spells[i]->StillCasting();
    }
    spell_casting[i] = m_spells[i]->spellCasting;
    m_spells[i]->Update(dt, glm::mat4(1.0f), 1, false, zeroVec);

    //updating light source position
    spell_position[i] = m_spells[i]->GetLocationVector();
  }


  //if(game_running) {
    for (int i = 0; i < (NUM_SPELLS / 2); i++) {
      if (Collide(m_spells[i]->GetLocationVector(), m_enemy->GetLocationVector()))  //Enemy hit by spell
      {
        std::cout << "Enemy ";
        m_enemy->ReduceHealth();
        m_spells[i]->EndCast();
      }
    }

    for (int i = (NUM_SPELLS / 2); i < NUM_SPELLS; i++) {
      if (Collide(m_spells[i]->GetLocationVector(), m_wiz1->GetLocationVector()))  //Player hit by spell
      {
        std::cout << "Player ";
        m_wiz1->ReduceHealth();
        m_spells[i]->EndCast();
      }
    }


  //}

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


        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "gSampler"), 0);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "nSampler"), 1);

        glUniform1i(m_useNorm, (GLint) 0);

        //Send in Light direction and color
        //glUniform1iv(m_calcSpellLight, 4, (GLint*) spell_casting[0]);
/*
          glUniform1i(m_calcSpellLight, spell_casting[0]);
          glUniform3fv(m_pointSources, 1, glm::value_ptr(spell_position[0]));
          glUniform3fv(m_pointSourceColor, 1, glm::value_ptr(spell_colors[0]));
*/
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[0]"), 1, (GLfloat*) &spell_position[0]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[0]"), 1, (GLfloat*) &spell_colors[0]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[0]"), spell_casting[0]);


        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[1]"), 1, (GLfloat*) &spell_position[1]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[1]"), 1, (GLfloat*) &spell_colors[1]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[1]"), spell_casting[1]);


        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[2]"), 1, (GLfloat*) &spell_position[2]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[2]"), 1, (GLfloat*) &spell_colors[2]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[2]"), spell_casting[2]);


        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[3]"), 1, (GLfloat*) &spell_position[3]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[3]"), 1, (GLfloat*) &spell_colors[3]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[3]"), spell_casting[3]);


        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[4]"), 1, (GLfloat*) &spell_position[4]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[4]"), 1, (GLfloat*) &spell_colors[4]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[4]"), spell_casting[4]);


        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "pointSources[5]"), 1, (GLfloat*) &spell_position[5]);
        glUniform3fv(glGetUniformLocation(m_phong->GetProgram(), "lightSourceColor[5]"), 1, (GLfloat*) &spell_colors[5]);
        glUniform1i(glGetUniformLocation(m_phong->GetProgram(), "calcLightSource[5]"), spell_casting[5]);










        //glUniform3fv(m_pointSources, 4, (GLfloat*) &spell_position[0]);
        //glUniform3fv(m_pointSourceColor, 4, (GLfloat*) &spell_colors[0]);


        glUniform3fv(m_lightDirection, 1, glm::value_ptr(l_D)); //skybox
        glUniform3fv(m_lightColor, 1, glm::value_ptr(l_C)); //skybox


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

       // glUniform1i(m_useNorm, (GLint) 1);
        for(int i = 0; i < m_ground->meshes.size(); i++) {    //ground is mesh 17
          if(i != 14 )     //i!=14
            m_ground->meshes[i].Draw();
        }



       // glUniform1i(m_useNorm, (GLint) 0);

        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_tree->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_tree->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_tree->specular_size);
        m_tree->Render();

        for(int i = 0; i < 5; i++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_fence[i]->GetModel()));
          glUniform1f(m_specular_brightness, (GLfloat) m_fence[i]->specular_brightness);
          glUniform1i(m_specular_size, (GLint) m_fence[i]->specular_size);
          m_fence[i]->Render();
        }

        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rock1->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_rock1->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_rock1->specular_size);
        m_rock1->Render();

        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rock2->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_rock2->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_rock2->specular_size);
        m_rock2->Render();

        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_well->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_well->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_well->specular_size);
        m_well->Render();

/*
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_wiz1->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_wiz1->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_wiz1->specular_size);
        m_wiz1->Render();
*/

        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_grass1->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) m_grass1->specular_brightness);
        glUniform1i(m_specular_size, (GLint) m_grass1->specular_size);
        m_grass1->Render();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_enemySprite->GetModel()));
          glUniform1f(m_specular_brightness, (GLfloat) m_enemySprite->specular_brightness);
          glUniform1i(m_specular_size, (GLint) m_enemySprite->specular_size);

          for (int i = 0; i < 14; i++) {
            if ( i!=2 && i != 1 && i != 0) {
              m_enemySprite->meshes[i].Draw();
            }
          }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(tester->GetModel()));
        glUniform1f(m_specular_brightness, (GLfloat) tester->specular_brightness);
        glUniform1i(m_specular_size, (GLint) tester->specular_size);
        tester->Render();
*/



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

      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_tree->GetModel()));
      m_tree->Render();

      for(int i = 0; i < 5; i++) {
        glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_fence[i]->GetModel()));
        m_fence[i]->Render();
      }

      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_rock1->GetModel()));
      m_rock1->Render();

      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_rock2->GetModel()));
      m_rock2->Render();

      glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_well->GetModel()));
      m_well->Render();

    }
    m_texture->Enable();


  glUniformMatrix4fv(m_tprojectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_tviewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  //glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_ground->GetModel()));
  //m_ground->Render();

  glUniformMatrix4fv(m_tmodelMatrix, 1, GL_FALSE, glm::value_ptr(m_enemySprite->GetModel()));
  m_enemySprite->meshes[0].Draw();

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

  m_color->Enable();

  glUniformMatrix4fv(m_cPM, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_cVM, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
  glUniform3fv(m_cCamPos, 1, glm::value_ptr(m_camera->cameraPosition));


    glUniformMatrix4fv(m_cMM, 1, GL_FALSE, glm::value_ptr(m_enemySprite->GetModel()));
    glUniform3fv(m_cColor, 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
    m_enemySprite->meshes[1].Draw();
    m_enemySprite->meshes[2].Draw();


  for(int i = 0; i < NUM_SPELLS; i++) {

    if (m_spells[i]->spellCasting) {

      glUniformMatrix4fv(m_cMM, 1, GL_FALSE, glm::value_ptr(m_spells[i]->GetModel()));

      glUniform3fv(m_cColor, 1, glm::value_ptr(spell_colors[i]));

      m_spells[i]->Render();
    }
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

bool Graphics::Collide(glm::vec3 objLocation1, glm::vec3 objLocation2)
{
    if(objLocation1.x < (objLocation2.x + .5) and
       objLocation1.x > (objLocation2.x - .5) and
       objLocation1.z < (objLocation2.z + .5) and
       objLocation1.z > (objLocation2.z - .5))
	return true;

    return false;
}
bool Graphics::GameOver()
{
  if (m_enemy->GetCurrentHealth() <= 0) {
    std::cout << "You are great!" << std::endl;
    game_running = false;
    m_enemy->SetCurrentHealth(100);
    m_wiz1->SetCurrentHealth(100);
    exit(EXIT_SUCCESS);
    //Player Wins Game
    return true;
  }
  else if (m_wiz1->GetCurrentHealth() <= 0) {
      std::cout << "You are not great!" << std::endl;
      game_running = false;
      m_enemy->SetCurrentHealth(100);
      m_wiz1->SetCurrentHealth(100);
      exit(EXIT_FAILURE);
      //Player Loses Game
      return true;
  }

  return false;

}

