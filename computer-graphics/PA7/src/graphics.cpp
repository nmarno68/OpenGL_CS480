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


  planet_view = false;
  target_planet = -1;
  scaled_view = false;
  top_view = false;

  //create objects
  m_milkyway = new Object("milkyway.obj");

  m_Sun = new Object("sun.obj");

  m_mars = new Object ("mars.obj");
  m_phobos = new Object("phobos.obj");
  m_deimos = new Object("deimos.obj");

  m_venus = new Object ("venus.obj");

  m_earth = new Object("earth2.obj");
  m_moon = new Object("moon.obj");

  m_mercury = new Object ("mercury.obj");

  m_jupiter = new Object ("jupiter.obj");
  m_ganymede = new Object ("ganymede.obj");
  m_callisto = new Object ("callisto.obj");
  m_io = new Object ("io.obj");
  m_europa = new Object ("europa.obj");

  m_saturn = new Object("Saturn.obj");
  m_titan = new Object("titon.obj");
  m_enceladus = new Object("enceladus.obj");

  m_neptune = new Object ("neptune.obj");
  m_triton = new Object("triton.obj");

  m_uranus = new Object ("uranus.obj");
  m_titania = new Object ("titania.obj");
  m_oberon = new Object ("oberon.obj");
  m_umbriel = new Object ("umbriel.obj");
  m_ariel = new Object ("ariel.obj");
  m_miranda = new Object ("miranda.obj");

  m_secret = new Object("sun.obj");
  m_pluto = new Object ("pluto.obj");
  m_charon = new Object("charon.obj");



  //Set the object values - float o_vel, float r_vel, float o_width, float o_length, float new_scale, tip, x_axis, y_axis, z_axis, start_angle, backwards
  m_milkyway->SetValues(0, 0, 0, 0, 700, 0, 0, 1.0, 0, 0, 0);

  m_Sun->SetValues( 0,.0002, 0, 0, 2, 0, 0.0, 1.0, 0.0, 0, 0);                              //start angle just starts the orbit in a different place in the circle
                                                                                            //in terms of pi. Ex. M_PI would start the orbit halfway around the sun
                                                                                            //this is needed for moons with the same orbit, and pluto and charon because
                                                                                            //they orbit each other. I already set them
  m_mars->SetValues(.00026, .002, 10, 10, .005, 0, -0.4, 1, -0.2, .2*M_PI, 0);             //for the moons, lets just have them all the same distance from the planet
  m_phobos->SetValues(.0005, 0.002, 0.1, 0.1, 0.00125, 0, 0, 1.0, 0, 0, 0);                 //for simplicity sake
  m_deimos->SetValues(.0005, 0.002, 0.1, 0.1, 0.00125, 0, 0, 1.0, 0, M_PI, 0);


  m_venus->SetValues(.00081, .003, 6, 6, .01, 0, 0, 1, 0, 1.3*M_PI, 1);


  m_earth->SetValues(.0005, .005825, 8, 8, .01, 0, -0.4, 1.0, -0.2, 0, 0);
  m_moon->SetValues(.01825, .01825, .05, .05, .004, -.03, -0.4, 1.0, -0.2, 0, 0);


  m_mercury->SetValues(.002, .0025, 4, 4, .005, 0, 0, 1, 0, .4*M_PI, 0);


  m_jupiter->SetValues(.000041, .003, 40, 40, .5, 0, 0, 1, 0, 1.7*M_PI, 0);
  m_ganymede->SetValues(.0005, 0.002, 1.5, 1.5, .01, 0, 0, 1.0, 0, .5 * M_PI, 0);             //Needs values
  m_callisto->SetValues(.0005, 0.002, 1.5, 1.5, .01, 0, 0, 1.0, 0, M_PI, 0);             //Needs values
  m_io->SetValues(.0005, 0.002, 1.5, 1.5, .01, 0, 0, 1.0, 0, 1.5*M_PI, 0);                   //Needs values
  m_europa->SetValues(.0005, 0.002, 1.5, 1.5, 0.01, 0, 0, 1.0, 0, 0, 0);               //Needs values


  m_saturn->SetValues(.000017, 0.005, 80, 80, .25, 10, -0.4, 1.0, -0.2, .25*M_PI, 0);
  m_titan->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, M_PI, 0);                //Needs values
  m_enceladus->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, 0, 0);            //Needs values


  m_neptune->SetValues(.000003, .005, 200, 200, .25, 0, -0.4, 1, -0.2, 0, 0);
  m_triton->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, 0, 0);               //Needs values


  m_uranus->SetValues(.000006, .003, 160, 160, .25, 0, 1, 0, .5, 1.8* M_PI, 0);
  m_titania->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, .4 * M_PI, 0);              //Needs values
  m_oberon->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, .8 * M_PI, 0);               //Needs values
  m_umbriel->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, 1.2 * M_PI, 0);              //Needs values
  m_ariel->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, 1.6*M_PI, 0);                //Needs values
  m_miranda->SetValues(.0005, 0.002, 1, 1, 0.01, 0, 0, 1.0, 0, 0, 0);              //Needs values

  //pluto and charon
  m_secret->SetValues(.000002, 0, 250, 250, 0, 20, 0, 1.0, 0, .7*M_PI, 0);
  m_pluto->SetValues(.005, .03, .3, .3, .008, 0, 0, 1, 0, 0, 0);
  m_charon->SetValues(.005, .02, .3, .3, .008, 0, 0, 1, 0, M_PI, 0);




  //Setting Scaled Values - float s_scale, float s_width, float s_length, x, y, z

  m_Sun->SetScaledValues(10, 0, 0, 0, 0, 0, 0);

  m_mars->SetScaledValues(.5, 50, 50, 3, 0, 3, 0);
  m_phobos->SetScaledValues(.066, 4, 4, 0, 0, 0, 0);
  m_deimos->SetScaledValues(.066, 4, 4, 0, 0, 0, 0);


  m_venus->SetScaledValues(.9, 30, 30, 0, 0, 0, 0);


  m_earth->SetScaledValues(1, 40, 40, 0, 0, 0, 0);
  m_moon->SetScaledValues(.3, 2.75, 2.75, 0, 0, 0, -1);


  m_mercury->SetScaledValues(.4, 20, 20, 0, 0, -5, 0);


  m_jupiter->SetScaledValues(5.6, 70, 70, 0, 0, 0, 0);
  m_ganymede->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);
  m_callisto->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);
  m_io->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);
  m_europa->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);


  m_saturn->SetScaledValues(4.725, 110, 110, 0, 0, 0, 10);
  m_titan->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);
  m_enceladus->SetScaledValues(.5, 15, 15, 0, 0, 0, 0);


  m_neptune->SetScaledValues(1.9, 170, 170, 0, 0, 0, 0);
  m_triton->SetScaledValues(.2, 10, 10, 0, 0, 0, 0);


  m_uranus->SetScaledValues(2, 140, 140, 0, 0, 0, 0);
  m_titania->SetScaledValues(.2, 10, 10, 0, 0, 0, 0);
  m_oberon->SetScaledValues(.2, 10, 10, 0, 0, 0, 0);
  m_umbriel->SetScaledValues( .2, 10, 10, 0, 0, 0, 0);
  m_ariel->SetScaledValues( .2, 10, 10, 0, 0, 0, 0);
  m_miranda->SetScaledValues( .2, 10, 10, 0, 0, 0, 0);

  //pluto and charon
  m_secret->SetScaledValues(0, 190, 190, -8, 0, 15, 20);
  m_pluto->SetScaledValues( 1, 4, 4, 0, 0, 0, 0);
  m_charon->SetScaledValues( 1, 4, 4, 0, 0, 0, 0);





  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER, "textureShaders"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, "textureShaders"))
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



  //
  //setup orbit drawing shaders
  //
  m_orbit_shader = new Shader();
  if(!m_orbit_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_orbit_shader->AddShader(GL_VERTEX_SHADER, "orbitShaders"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_orbit_shader->AddShader(GL_FRAGMENT_SHADER, "orbitShaders"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_orbit_shader->Finalize())
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




  m_orbitProjection = m_orbit_shader->GetUniformLocation("projectionMatrix");
  if (m_orbitProjection == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_orbitView = m_orbit_shader->GetUniformLocation("viewMatrix");
  if (m_orbitView == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_orbitModel = m_orbit_shader->GetUniformLocation("modelMatrix");
  if (m_orbitModel == INVALID_UNIFORM_LOCATION)
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
  if(scaled_view) {
    m_camera->cameraSpeed = .5;
  }
  else{
    m_camera->cameraSpeed = .5;
  }

  m_Sun->Update(dt, glm::mat4(1.0f));

  m_mars->Update(dt, m_Sun->GetLocation());
  m_phobos->Update(dt, m_mars->GetLocation());
  m_deimos->Update(dt, m_mars->GetLocation());

  m_venus->Update(dt,m_Sun->GetLocation());

  m_earth->Update(dt, m_Sun->GetLocation());
  m_moon->Update(dt, m_earth->GetLocation());

  m_mercury->Update(dt, m_Sun->GetLocation());

  m_jupiter->Update(dt, m_Sun->GetLocation());
  m_ganymede->Update(dt, m_jupiter->GetLocation());
  m_callisto->Update(dt, m_jupiter->GetLocation());
  m_io->Update(dt, m_jupiter->GetLocation());
  m_europa->Update(dt, m_jupiter->GetLocation());

  m_saturn->Update(dt, m_Sun->GetLocation());
  m_titan->Update(dt, m_saturn->GetLocation());
  m_enceladus->Update(dt, m_saturn->GetLocation());

  m_neptune->Update(dt, m_Sun->GetLocation());
  m_triton->Update(dt, m_neptune->GetLocation());

  m_uranus->Update(dt, m_Sun->GetLocation());
  m_titania->Update(dt, m_uranus->GetLocation());
  m_oberon->Update(dt, m_uranus->GetLocation());
  m_umbriel->Update(dt, m_uranus->GetLocation());
  m_ariel->Update(dt, m_uranus->GetLocation());
  m_miranda->Update(dt, m_uranus->GetLocation());

  m_secret->Update(dt, m_Sun->GetLocation());
  m_pluto->Update(dt, m_secret->GetLocation());
  m_charon->Update(dt, m_secret->GetLocation());

  if(planet_view)
  {
    switch(target_planet)
    {
      case 0:
        if(scaled_view)
        {
          m_camera->PlanetView(m_Sun->GetLocationVector(), glm::vec3(0.0, 0.0, 35.0));
        }
        else {
          m_camera->PlanetView(m_Sun->GetLocationVector(), glm::vec3(0.0, 0.0, 10.0));
        }
        break;

      case 1:
        if(scaled_view)
        {
          m_camera->PlanetView(m_mercury->GetLocationVector(), glm::vec3(0.0, 0.0, 1.75));
        }
        else {
          m_camera->PlanetView(m_mercury->GetLocationVector(), glm::vec3(0.0, 0.0, .075));
        }
        break;

      case 2:
        if(scaled_view)
        {
          m_camera->PlanetView(m_venus->GetLocationVector(), glm::vec3(0.0, 0.0, 4.0));
        }
        else {
          m_camera->PlanetView(m_venus->GetLocationVector(), glm::vec3(0.0, 0.0, .075));
        }
        break;

      case 3:
        if(scaled_view)
        {
          m_camera->PlanetView(m_earth->GetLocationVector(), glm::vec3(0.0, 0.0, 5.0));
        }
        else {
          m_camera->PlanetView(m_earth->GetLocationVector(), glm::vec3(0.0, 0.0, .095));
        }
        break;

      case 4:
        if(scaled_view)
        {
          m_camera->PlanetView(m_mars->GetLocationVector(), glm::vec3(0.0, 0.0, 3));
        }
        else {
          m_camera->PlanetView(m_mars->GetLocationVector(), glm::vec3(0.0, 0.0, 0.075));
        }
        break;

      case 5:
        if(scaled_view)
        {
          m_camera->PlanetView(m_jupiter->GetLocationVector(), glm::vec3(0.0, 0.0, 20.0));
        }
        else {
          m_camera->PlanetView(m_jupiter->GetLocationVector(), glm::vec3(0.0, 0.0, 3.0));
        }
        break;

      case 6:
        if(scaled_view)
        {
          m_camera->PlanetView(m_saturn->GetLocationVector(), glm::vec3(0.0, 0, 20.0));
        }
        else {
          m_camera->PlanetView(m_saturn->GetLocationVector(), glm::vec3(0.0, 0, 2.0));
        }
        break;

      case 7:
        if(scaled_view)
        {
          m_camera->PlanetView(m_uranus->GetLocationVector(), glm::vec3(0.0, 0.0, 13.0));
        }
        else {
          m_camera->PlanetView(m_uranus->GetLocationVector(), glm::vec3(0.0, 0.0, 2.0));
        }
        break;

      case 8:
        if(scaled_view)
        {
          m_camera->PlanetView(m_neptune->GetLocationVector(), glm::vec3(0.0, 0.0, 13.0));
        }
        else {
          m_camera->PlanetView(m_neptune->GetLocationVector(), glm::vec3(0.0, 0.0, 2.0));
        }
        break;

      case 9:
        if(scaled_view)
        {
          m_camera->PlanetView(m_secret->GetLocationVector(), glm::vec3(0.0, 0.0, 8));
        }
        else {
          m_camera->PlanetView(m_secret->GetLocationVector(), glm::vec3(0.0, 0.0, .5));
        }
        break;

      default:
        break;

    }

  }
  m_milkyway->Update(dt, m_camera->GetLocation());


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
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_milkyway->GetModel()));

  m_milkyway->Render();


  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_Sun->GetModel()));

  m_Sun->Render();




  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mars->GetModel()));

  m_mars->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_deimos->GetModel()));

  m_deimos->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_phobos->GetModel()));

  m_phobos->Render();



  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_venus->GetModel()));

  m_venus->Render();




  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_earth->GetModel()));

  m_earth->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_moon->GetModel()));

  m_moon->Render();




  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mercury->GetModel()));

  m_mercury->Render();




  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_jupiter->GetModel()));

  m_jupiter->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_callisto->GetModel()));

  m_callisto->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_io->GetModel()));

  m_io->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ganymede->GetModel()));

  m_ganymede->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_europa->GetModel()));

  m_europa->Render();




  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_saturn->GetModel()));

  m_saturn->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_titan->GetModel()));

  m_titan->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_enceladus->GetModel()));

  m_enceladus->Render();



  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_neptune->GetModel()));

  m_neptune->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_triton->GetModel()));

  m_triton->Render();



  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_uranus->GetModel()));

  m_uranus->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_titania->GetModel()));

  m_titania->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_umbriel->GetModel()));

  m_umbriel->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_oberon->GetModel()));

  m_oberon->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ariel->GetModel()));

  m_ariel->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_miranda->GetModel()));

  m_miranda->Render();



  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_secret->GetModel()));

  m_secret->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pluto->GetModel()));

  m_pluto->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_charon->GetModel()));

  m_charon->Render();


  if(scaled_view)
  {
    //activate shader
    m_orbit_shader->Enable();

    glUniformMatrix4fv(m_orbitProjection, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_orbitView, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

    glUniformMatrix4fv(m_orbitModel, 1, GL_FALSE, glm::value_ptr(m_Sun->GetLocation()));

    //each planet call render orbit
    m_mercury->RenderOrbit();
    m_venus->RenderOrbit();
    m_earth->RenderOrbit();
    m_mars->RenderOrbit();
    m_jupiter->RenderOrbit();
    m_saturn->RenderOrbit();
    m_uranus->RenderOrbit();
    m_neptune->RenderOrbit();
    m_secret->RenderOrbit();
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

  m_titan->IncreaseRotationSpeed();
  m_titan->IncreaseOrbitSpeed();

  m_enceladus->IncreaseRotationSpeed();
  m_enceladus->IncreaseOrbitSpeed();


  m_mars->IncreaseRotationSpeed();
  m_mars->IncreaseOrbitSpeed();

  m_deimos->IncreaseRotationSpeed();
  m_deimos->IncreaseOrbitSpeed();

  m_phobos->IncreaseRotationSpeed();
  m_phobos->IncreaseOrbitSpeed();


  m_venus->IncreaseRotationSpeed();
  m_venus->IncreaseOrbitSpeed();


  m_mercury->IncreaseRotationSpeed();
  m_mercury->IncreaseOrbitSpeed();


  m_jupiter->IncreaseRotationSpeed();
  m_jupiter->IncreaseOrbitSpeed();

  m_ganymede->IncreaseRotationSpeed();
  m_ganymede->IncreaseOrbitSpeed();

  m_callisto->IncreaseRotationSpeed();
  m_callisto->IncreaseOrbitSpeed();

  m_io->IncreaseRotationSpeed();
  m_io->IncreaseOrbitSpeed();

  m_europa->IncreaseRotationSpeed();
  m_europa->IncreaseOrbitSpeed();


  m_neptune->IncreaseRotationSpeed();
  m_neptune->IncreaseOrbitSpeed();

  m_triton->IncreaseRotationSpeed();
  m_triton->IncreaseOrbitSpeed();

  m_uranus->IncreaseRotationSpeed();
  m_uranus->IncreaseOrbitSpeed();

  m_titania->IncreaseRotationSpeed();
  m_titania->IncreaseOrbitSpeed();

  m_oberon->IncreaseRotationSpeed();
  m_oberon->IncreaseOrbitSpeed();

  m_umbriel->IncreaseRotationSpeed();
  m_umbriel->IncreaseOrbitSpeed();

  m_ariel->IncreaseRotationSpeed();
  m_ariel->IncreaseOrbitSpeed();

  m_miranda->IncreaseRotationSpeed();
  m_miranda->IncreaseOrbitSpeed();

  m_pluto->IncreaseRotationSpeed();
  m_pluto->IncreaseOrbitSpeed();

  m_charon->IncreaseRotationSpeed();
  m_charon->IncreaseOrbitSpeed();
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

  m_titan->DecreaseRoationSpeed();
  m_titan->DecreaseOrbitSpeed();

  m_enceladus->DecreaseRoationSpeed();
  m_enceladus->DecreaseOrbitSpeed();



  m_mars->DecreaseRoationSpeed();
  m_mars->DecreaseOrbitSpeed();

  m_deimos->DecreaseRoationSpeed();
  m_deimos->DecreaseOrbitSpeed();

  m_phobos->DecreaseRoationSpeed();
  m_phobos->DecreaseOrbitSpeed();


  m_venus->DecreaseRoationSpeed();
  m_venus->DecreaseOrbitSpeed();


  m_mercury->DecreaseRoationSpeed();
  m_mercury->DecreaseOrbitSpeed();


  m_jupiter->DecreaseRoationSpeed();
  m_jupiter->DecreaseOrbitSpeed();

  m_ganymede->DecreaseRoationSpeed();
  m_ganymede->DecreaseOrbitSpeed();

  m_callisto->DecreaseRoationSpeed();
  m_callisto->DecreaseOrbitSpeed();

  m_io->DecreaseRoationSpeed();
  m_io->DecreaseOrbitSpeed();

  m_europa->DecreaseRoationSpeed();
  m_europa->DecreaseOrbitSpeed();


  m_neptune->DecreaseRoationSpeed();
  m_neptune->DecreaseOrbitSpeed();

  m_triton->DecreaseRoationSpeed();
  m_triton->DecreaseOrbitSpeed();


  m_uranus->DecreaseRoationSpeed();
  m_uranus->DecreaseOrbitSpeed();

  m_umbriel->DecreaseRoationSpeed();
  m_umbriel->DecreaseOrbitSpeed();

  m_titania->DecreaseRoationSpeed();
  m_titania->DecreaseOrbitSpeed();

  m_oberon->DecreaseRoationSpeed();
  m_oberon->DecreaseOrbitSpeed();

  m_miranda->DecreaseRoationSpeed();
  m_miranda->DecreaseOrbitSpeed();

  m_ariel->DecreaseRoationSpeed();
  m_ariel->DecreaseOrbitSpeed();


  m_pluto->DecreaseRoationSpeed();
  m_pluto->DecreaseOrbitSpeed();

  m_charon->DecreaseRoationSpeed();
  m_charon->DecreaseOrbitSpeed();

}

void Graphics::resetAll()
{
  m_secret->ResetAll();

  m_Sun->ResetAll();

  m_earth->ResetAll();

  m_moon->ResetAll();

  m_saturn->ResetAll();

  m_titan->ResetAll();
  m_enceladus->ResetAll();


  m_mars->ResetAll();

  m_deimos->ResetAll();
  m_phobos->ResetAll();


  m_venus->ResetAll();


  m_mercury->ResetAll();


  m_jupiter->ResetAll();

  m_ganymede->ResetAll();
  m_callisto->ResetAll();
  m_io->ResetAll();
  m_europa->ResetAll();


  m_neptune->ResetAll();
  m_triton->ResetAll();


  m_uranus->ResetAll();

  m_umbriel->ResetAll();
  m_ariel->ResetAll();
  m_miranda->ResetAll();
  m_titania->ResetAll();
  m_oberon->ResetAll();


  m_pluto-> ResetAll();
  m_charon->ResetAll();

}

void Graphics::scaledView()
{
  m_Sun->UseScaled();
  m_mercury->UseScaled();
  m_venus->UseScaled();
  m_earth->UseScaled();
  m_moon->UseScaled();
  m_mars->UseScaled();
  m_deimos->UseScaled();
  m_phobos->UseScaled();
  m_jupiter->UseScaled();
  m_ganymede->UseScaled();
  m_callisto->UseScaled();
  m_io->UseScaled();
  m_europa->UseScaled();
  m_saturn->UseScaled();
  m_titan->UseScaled();
  m_enceladus->UseScaled();
  m_uranus->UseScaled();
  m_titania->UseScaled();
  m_oberon->UseScaled();
  m_umbriel->UseScaled();
  m_ariel->UseScaled();
  m_miranda->UseScaled();
  m_neptune->UseScaled();
  m_triton->UseScaled();
  m_pluto->UseScaled();
  m_charon->UseScaled();
  m_secret->UseScaled();
}

void Graphics::actualView()
{
  m_Sun->UseActual();
  m_mercury->UseActual();
  m_venus->UseActual();
  m_earth->UseActual();
  m_moon->UseActual();
  m_mars->UseActual();
  m_deimos->UseActual();
  m_phobos->UseActual();
  m_jupiter->UseActual();
  m_ganymede->UseActual();
  m_callisto->UseActual();
  m_io->UseActual();
  m_europa->UseActual();
  m_saturn->UseActual();
  m_titan->UseActual();
  m_enceladus->UseActual();
  m_uranus->UseActual();
  m_titania->UseActual();
  m_oberon->UseActual();
  m_umbriel->UseActual();
  m_ariel->UseActual();
  m_miranda->UseActual();
  m_neptune->UseActual();
  m_triton->UseActual();
  m_pluto->UseActual();
  m_charon->UseActual();
  m_secret->UseActual();

}