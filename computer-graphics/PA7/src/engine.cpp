
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

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();                                   //////////////////////PA2//////////////////////////
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_newEvent = false;
    m_graphics->Render();

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
    switch (m_event.key.keysym.sym) {  //come back to controls later for individual planets maybe
      case SDLK_ESCAPE:                 //the control functions still exist in the object class
        m_running = false;
        break;

      case SDLK_w:
        m_graphics->m_camera->MoveForward();
        break;

      case SDLK_s:
        m_graphics->m_camera->MoveBackward();
        break;

      case SDLK_a:
        m_graphics->m_camera->MoveLeft();
        break;

      case SDLK_d:
        m_graphics->m_camera->MoveRight();
        break;

      case SDLK_UP:
        m_graphics->m_camera->MoveUp();
        break;

      case SDLK_DOWN:
        m_graphics->m_camera->MoveDown();
        break;

      case SDLK_0:
        m_graphics->target_planet = 0;
        break;

      case SDLK_1:
        m_graphics->target_planet = 1;
        break;

      case SDLK_2:
        m_graphics->target_planet = 2;
        break;

      case SDLK_3:
        m_graphics->target_planet = 3;
        break;

      case SDLK_4:
        m_graphics->target_planet = 4;
        break;

      case SDLK_p:
        m_graphics->IncSimSpeed();
        break;

      case SDLK_o:
        m_graphics->DecSimSpeed();
        break;

      case SDLK_q:
        m_graphics->resetAll();

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
