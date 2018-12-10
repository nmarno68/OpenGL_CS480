

#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
  m_plungerForce = 6.31;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
  m_plungerForce = 6.306;
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

        //Enable FPS mode
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

      case SDLK_w:
        /*  glm::vec3 mf;
          mf = m_graphics->m_camera->cameraPosition + m_graphics->m_camera->cameraFront;
          mf.y = 0;
          m_graphics->m_wiz1->m_rigidBody->applyForce(btVector3(mf.x, mf.y, mf.z) * 5, btVector3(0.0, 0.0, 0.0));
          */
          m_graphics->m_camera->MoveForward();
          break;
      case SDLK_a:
          m_graphics->m_camera->MoveLeft();
          break;
      case SDLK_d:
          m_graphics->m_camera->MoveRight();
          break;
      case SDLK_s:
          m_graphics->m_camera->MoveBackward();
          break;
      case SDLK_SPACE:
          m_graphics->m_camera->MoveUp();
          break;
      case SDLK_f:
        if(m_graphics->skybox_used == 1) {
          m_graphics->skybox_used = 2;
          m_graphics->l_C = glm::vec3(1.0, .8, .73);
          m_graphics->l_D = glm::vec3(0.0, .3, 1.0);
        }
        else {
          m_graphics->skybox_used = 1;
          m_graphics->l_C = glm::vec3(1.0, 1.0, 1.0);
          m_graphics->l_D = glm::vec3(0.3, 1.0, 0.0);
        }
        break;
      case SDLK_p:
        m_graphics->normals = !m_graphics->normals;
        break;


    }
  }
  else if (m_event.type == SDL_KEYUP)
  {
    switch (m_event.key.keysym.sym)
    {
      default:
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
