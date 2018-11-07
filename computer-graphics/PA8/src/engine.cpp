
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  //Menu Initialization
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void) io;

  ImGui_ImplSDL2_InitForOpenGL(m_window->GetSDLWindow(), m_window->GetContext());
  ImGui_ImplOpenGL3_Init("#version 330");
  ImGui::StyleColorsClassic();


  submenu = 0;
  subsubmenu = 0;


  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    //Menu setup for frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window->GetSDLWindow());
    ImGui::NewFrame();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&m_event);
      Keyboard();
    }


    //menu code here plz
    {
      ImGui::Begin("Lighting Control");
      ImGui::Checkbox("Phong/Gourand", &m_graphics->phong);
      ImGui::SliderFloat("Ambient Strength", &m_graphics->ambientStrength, 0.0, 1.0);
      ImGui::Text("Ambient Color");
      ImGui::SliderFloat("Red", &m_graphics->ambient_color[0], 0.0, 1.0);
      ImGui::SliderFloat("Green", &m_graphics->ambient_color[1], 0.0, 1.0);
      ImGui::SliderFloat("Blue", &m_graphics->ambient_color[2], 0.0, 1.0);

      ImGui::End();


      ImGui::Begin("Spotlight Control");
      ImGui::Checkbox("Turn on spotlight", &m_graphics->spot);
      if(m_graphics->spot)
      {
         ImGui::Checkbox("Hard edge/Soft edge", &m_graphics->hard_edge);
      }
      ImGui::SliderFloat("Spotlight Size", &m_graphics->spotlight_size, 200, .001);
      ImGui::SliderFloat("Spotlight Brightness", &m_graphics->spotlight_brightness, 0, 1);
      ImGui::End();


      ImGui::Begin("Specular Controls");
      ImGui::Text("Specular Brightness");
      ImGui::SliderFloat("Ball", &m_graphics->m_ball->specular_brightness, 0, 1);
      ImGui::SliderFloat("Board", &m_graphics->m_boardy->specular_brightness, 0, 1);
      ImGui::SliderFloat("Cube", &m_graphics->m_cube->specular_brightness, 0, 1);
      ImGui::SliderFloat("Cylinder", &m_graphics->m_cyl->specular_brightness, 0, 1);
      ImGui::End();
    }







    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_newEvent = false;

    m_graphics->Render();

    //Render menus
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    bool shift = false;

    //Using the actual numerical value of SDLK_SHIFTs because directly comparing
    //Was not working for some reason
    if((m_event.key.keysym.mod == KMOD_LSHIFT) or ( m_event.key.keysym.mod == KMOD_RSHIFT))
    {
      shift = true;
    }
    // handle key down events here
    m_newEvent = true;

    //Handling keyboard events
    switch (m_event.key.keysym.sym) {
      case SDLK_ESCAPE:
        m_running = false;
        break;
/*
      case SDLK_e:
        if (m_graphics->m_camera->enableMouse) {
          SDL_SetRelativeMouseMode((SDL_bool) 0);
          m_graphics->m_camera->enableMouse = 0;
        }
        else {
          SDL_SetRelativeMouseMode((SDL_bool) 1);
          m_graphics->m_camera->enableMouse = 1;
        }
        break;
*/
				case SDLK_w:
					m_graphics->m_cube->m_rigidBody->applyForce(btVector3(-.2, 0, 0), btVector3(0, 0, 0));
					break;
				case SDLK_a:
					m_graphics->m_cube->m_rigidBody->applyForce(btVector3(0, 0, .2), btVector3(0, 0, 0));
					break;
				case SDLK_s:
					m_graphics->m_cube->m_rigidBody->applyForce(btVector3(.2, 0, 0), btVector3(0, 0, 0));
					break;
				case SDLK_d:
					m_graphics->m_cube->m_rigidBody->applyForce(btVector3(0, 0, -.2), btVector3(0, 0, 0));
					break;
				case SDLK_SPACE:
					m_graphics->m_cube->m_rigidBody->applyForce(btVector3(0, 1, 0), btVector3(0, 0, 0));
					break;

    }
}
  else if (m_event.type == SDL_MOUSEMOTION )
  {
    if(m_graphics->m_camera->enableMouse)
    {
      int x, y;
      x = m_event.motion.xrel;
      y = m_event.motion.yrel;
      m_graphics->m_camera->MouseMovement(x, y);
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}

